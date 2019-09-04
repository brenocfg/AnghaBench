#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct filesys_inode {struct filesys_inode* next; struct filesys_inode* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct filesys_inode* lru_head ; 
 struct filesys_inode* lru_tail ; 

__attribute__((used)) static void del_use (struct filesys_inode *I) {
  if (I->prev == NULL) {
    assert (lru_head == I);
    if (I->next == NULL) {
      lru_head = lru_tail = NULL;
    } else {
      lru_head = lru_head->next;
      lru_head->prev = NULL;
    }
  } else if (I->next == NULL) {
    assert (lru_tail == I);
    lru_tail = lru_tail->prev;
    lru_tail->next = NULL;
  } else {
    I->prev->next = I->next;
    I->next->prev = I->prev;
  }
  I->prev = I->next = NULL;
}