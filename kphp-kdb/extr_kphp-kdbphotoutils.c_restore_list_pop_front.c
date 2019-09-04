#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* next; struct TYPE_7__* prev; } ;
typedef  TYPE_1__ restore_list ;

/* Variables and functions */
 int /*<<< orphan*/  restore_list_connect (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  restore_list_free (TYPE_1__*) ; 

restore_list *restore_list_pop_front (restore_list *v) {
  restore_list *res;
  if (v->next == v) {
    res = NULL;
  } else {
    restore_list_connect (v->prev, v->next);
    res = v->next;
  }

  restore_list_connect (v, v);
  restore_list_free (v);
  return res;
}