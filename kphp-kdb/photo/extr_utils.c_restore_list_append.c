#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* prev; } ;
typedef  TYPE_1__ restore_list ;

/* Variables and functions */
 int /*<<< orphan*/  restore_list_connect (TYPE_1__*,TYPE_1__*) ; 

void restore_list_append (restore_list *v, restore_list *to_append) {
  //dbg ("restore_list_append %p %p\n", v->prev, v);
  restore_list *to_append_prev = to_append->prev;
  restore_list_connect (v->prev, to_append);
  restore_list_connect (to_append_prev, v);
}