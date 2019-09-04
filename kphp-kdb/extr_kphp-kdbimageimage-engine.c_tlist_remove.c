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
struct forth_request {scalar_t__ size; struct forth_request* next; struct forth_request* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,struct forth_request*) ; 

void tlist_remove (struct forth_request *L, struct forth_request *T) {
  vkprintf (4, "tlist_remove (%p)\n", T);
  struct forth_request *u = T->prev, *v = T->next;
  if (u == NULL && v == NULL) {
    return;
  }
  assert (u != NULL && v != NULL);
  u->next = v;
  v->prev = u;
  T->prev = T->next = NULL;
  L->size--;
  assert (L->size >= 0);
}