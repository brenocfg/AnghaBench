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
struct tl_token {struct tl_token* next; int /*<<< orphan*/  text; } ;

/* Variables and functions */
 int /*<<< orphan*/  cstr_dup (int /*<<< orphan*/ ) ; 
 struct tl_token* list_token_reverse (struct tl_token*) ; 
 struct tl_token* zmalloc0 (int) ; 

__attribute__((used)) static struct tl_token *tl_token_clone (struct tl_token *T) {
  struct tl_token *head = NULL;
  while (T != NULL) {
    struct tl_token *A = zmalloc0 (sizeof (struct tl_token));
    A->text = cstr_dup (T->text);
    A->next = head;
    head = A;
    T = T->next;
  }
  return list_token_reverse (head);
}