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

/* Variables and functions */
 int /*<<< orphan*/  access_miss_counters ; 
 int /*<<< orphan*/  access_success_counters ; 
 int /*<<< orphan*/  cache_stats_counter_relax (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_miss_counters ; 
 int /*<<< orphan*/  convert_success_counters ; 

void cache_stats_relax (void) {
  cache_stats_counter_relax (convert_success_counters);
  cache_stats_counter_relax (convert_miss_counters);
  cache_stats_counter_relax (access_success_counters);
  cache_stats_counter_relax (access_miss_counters);
}