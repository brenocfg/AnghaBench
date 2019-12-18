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
typedef  scalar_t__ u64 ;
struct latency_info {int io_interval; int cpu_interval; scalar_t__ interrupt_cnt; scalar_t__ latency_sum; scalar_t__ min_latency; scalar_t__ max_latency; scalar_t__ timer_start2; scalar_t__ timer_start1; } ;

/* Variables and functions */
 int octeon_get_clock_rate () ; 
 int octeon_get_io_clock_rate () ; 

__attribute__((used)) static void init_latency_info(struct latency_info *li, int startup)
{
	/* interval in milli seconds after which the interrupt will
	 * be triggered
	 */
	int interval = 1;

	if (startup) {
		/* Calculating by the amounts io clock and cpu clock would
		 *  increment in interval amount of ms
		 */
		li->io_interval = (octeon_get_io_clock_rate() * interval) / 1000;
		li->cpu_interval = (octeon_get_clock_rate() * interval) / 1000;
	}
	li->timer_start1 = 0;
	li->timer_start2 = 0;
	li->max_latency = 0;
	li->min_latency = (u64)-1;
	li->latency_sum = 0;
	li->interrupt_cnt = 0;
}