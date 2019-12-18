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
struct lmodule {int dummy; } ;

/* Variables and functions */
 int MAX_CPU_SAMPLES ; 
 int /*<<< orphan*/  cpus_load_timer ; 
 int /*<<< orphan*/  get_cpus_samples ; 
 int /*<<< orphan*/  timer_start_repeat (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct lmodule*) ; 

void
start_processor_tbl(struct lmodule *mod)
{

	/*
	 * Start the cpu stats collector
	 * The semantics of timer_start parameters is in "SNMP ticks";
	 * we have 100 "SNMP ticks" per second, thus we are trying below
	 * to get MAX_CPU_SAMPLES per minute
	 */
	cpus_load_timer = timer_start_repeat(100, 100 * 60 / MAX_CPU_SAMPLES,
	    get_cpus_samples, NULL, mod);
}