#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t type; } ;
typedef  TYPE_1__ event ;

/* Variables and functions */
 int /*<<< orphan*/  QINC (size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__** eq ; 
 size_t eq_l ; 
 int eq_n ; 
 scalar_t__ events_mem ; 
 int /*<<< orphan*/  events_memory ; 
 scalar_t__ evm_l ; 
 scalar_t__ get_event_size (TYPE_1__*) ; 
 int /*<<< orphan*/ * type_size ; 
 int /*<<< orphan*/  upd_q_st_delete (TYPE_1__*,size_t) ; 

void event_free (void) {
  assert (eq_n);
  if (*(int *)(events_mem + evm_l) == -1) {
    evm_l = 0;
  }
  event *e = (event *)(events_mem + evm_l);

  assert (eq[eq_l] == e);
  upd_q_st_delete (e, eq_l);
  eq_n--;
  eq[eq_l] = NULL;
  QINC(eq_l);
  type_size[e->type] -= get_event_size (e);
  events_memory -= get_event_size (e);
  evm_l += get_event_size (e);
}