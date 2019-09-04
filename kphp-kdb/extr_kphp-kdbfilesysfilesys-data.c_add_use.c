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
 struct filesys_inode* lru_head ; 
 struct filesys_inode* lru_tail ; 

__attribute__((used)) static void add_use (struct filesys_inode *I) {
  if (lru_tail == NULL) {
    lru_head = lru_tail = I;
    I->prev = I->next = NULL;
  } else {
    lru_tail->next = I;
    I->prev = lru_tail;
    I->next = NULL;
    lru_tail = I;
  }
}