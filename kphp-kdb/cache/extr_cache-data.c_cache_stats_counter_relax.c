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
struct amortization_counter_precise {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * TAT ; 
 int /*<<< orphan*/  amortization_counter_precise_increment (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stats_counters ; 

void cache_stats_counter_relax (struct amortization_counter_precise *C) {
  int i;
  for (i = 0; i < stats_counters; i++) {
    amortization_counter_precise_increment (&TAT[i], C++, 0);
  }
}