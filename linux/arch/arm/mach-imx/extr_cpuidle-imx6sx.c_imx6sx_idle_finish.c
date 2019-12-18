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
 int /*<<< orphan*/  cpu_do_idle () ; 
 int /*<<< orphan*/  flush_cache_all () ; 

__attribute__((used)) static int imx6sx_idle_finish(unsigned long val)
{
	/*
	 * for Cortex-A7 which has an internal L2
	 * cache, need to flush it before powering
	 * down ARM platform, since flushing L1 cache
	 * here again has very small overhead, compared
	 * to adding conditional code for L2 cache type,
	 * just call flush_cache_all() is fine.
	 */
	flush_cache_all();
	cpu_do_idle();

	return 0;
}