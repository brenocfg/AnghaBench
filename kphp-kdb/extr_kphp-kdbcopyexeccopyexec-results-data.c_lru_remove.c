#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct TYPE_3__* next; struct TYPE_3__* prev; } ;
typedef  TYPE_1__ transaction_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lru_size ; 

void lru_remove (transaction_t *T) {
  transaction_t *u = T->prev, *v = T->next;
  if (u == NULL && v == NULL) {
    return;
  }
  assert (u != NULL && v != NULL);
  u->next = v;
  v->prev = u;
  T->prev = T->next = NULL;
  lru_size--;
}