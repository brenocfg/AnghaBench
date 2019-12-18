#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* next; int /*<<< orphan*/ * values; } ;
struct TYPE_6__ {void* relaxation_time; int counters_mask; TYPE_2__ head; } ;
typedef  TYPE_1__ weights_vector_t ;
typedef  TYPE_2__ weights_counters_t ;

/* Variables and functions */
 int /*<<< orphan*/ * TAT ; 
 int /*<<< orphan*/  add_use_back (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  del_use (TYPE_1__*) ; 
 int ffs (int) ; 
 void* log_last_ts ; 
 int /*<<< orphan*/  time_amortization_table_fast_exp (int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static void weights_vector_relax (weights_vector_t *V) {
  const int dt = log_last_ts - V->relaxation_time;
  if (dt < 0) {
    return;
  }
  if (dt > 0) {
    weights_counters_t *C = &V->head;
    int mask = V->counters_mask;
    do {
      int o = ffs (mask) - 1;
      mask ^= 1 << o;
      o *= 32;
      int j;
      for (j = 0; j < 32; j++, o++) {
        C->values[j] *= time_amortization_table_fast_exp (TAT[o], dt);
      }
      C = C->next;
    } while (C);
    assert (!mask);
    V->relaxation_time = log_last_ts;
  }
  del_use (V);
  add_use_back (V);
}