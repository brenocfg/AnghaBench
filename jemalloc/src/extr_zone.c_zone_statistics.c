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
typedef  int /*<<< orphan*/  malloc_zone_t ;
struct TYPE_3__ {scalar_t__ size_allocated; scalar_t__ max_size_in_use; scalar_t__ size_in_use; scalar_t__ blocks_in_use; } ;
typedef  TYPE_1__ malloc_statistics_t ;

/* Variables and functions */

__attribute__((used)) static void
zone_statistics(malloc_zone_t *zone, malloc_statistics_t *stats) {
	/* We make no effort to actually fill the values */
	stats->blocks_in_use = 0;
	stats->size_in_use = 0;
	stats->max_size_in_use = 0;
	stats->size_allocated = 0;
}