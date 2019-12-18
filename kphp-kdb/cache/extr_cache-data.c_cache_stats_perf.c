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
struct amortization_counter_precise {double value; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int snprintf (char*,int,char*,char,double) ; 
 int stats_counters ; 

void cache_stats_perf (char *out, int olen, struct amortization_counter_precise *success, struct amortization_counter_precise *miss) {
  int i;
  for (i = 0; i <= stats_counters; i++) {
    double x = success->value, y = x + miss->value;
    x = 100.0 * x;
    x = (y < 1e-6) ? 0.0 : x / y;
    int l = snprintf (out, olen, "%c%.6lf", i ? ',' : '\t', x);
    assert (l < olen);
    olen -= l;
    out += l;
    success++;
    miss++;
  }
}