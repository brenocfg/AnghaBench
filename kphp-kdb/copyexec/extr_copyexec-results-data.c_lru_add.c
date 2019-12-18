#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; struct TYPE_4__* prev; } ;
typedef  TYPE_1__ transaction_t ;

/* Variables and functions */
 TYPE_1__ lru_list ; 
 int /*<<< orphan*/  lru_size ; 

void lru_add (transaction_t *T) {
  transaction_t *u = &lru_list, *v = u->next;
  u->next = T; T->prev = u;
  v->prev = T; T->next = v;
  lru_size++;
}