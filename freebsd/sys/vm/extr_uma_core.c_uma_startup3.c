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
 int /*<<< orphan*/  BOOT_RUNNING ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int /*<<< orphan*/ *) ; 
 int UMA_TIMEOUT ; 
 int /*<<< orphan*/  booted ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* counter_u64_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_divisor ; 
 int hz ; 
 int /*<<< orphan*/  uma_callout ; 
 void* uma_dbg_cnt ; 
 void* uma_skip_cnt ; 
 int /*<<< orphan*/  uma_timeout ; 
 int /*<<< orphan*/  zone_alloc_counters ; 
 int /*<<< orphan*/  zone_foreach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uma_startup3(void)
{

#ifdef INVARIANTS
	TUNABLE_INT_FETCH("vm.debug.divisor", &dbg_divisor);
	uma_dbg_cnt = counter_u64_alloc(M_WAITOK);
	uma_skip_cnt = counter_u64_alloc(M_WAITOK);
#endif
	zone_foreach(zone_alloc_counters);
	callout_init(&uma_callout, 1);
	callout_reset(&uma_callout, UMA_TIMEOUT * hz, uma_timeout, NULL);
	booted = BOOT_RUNNING;
}