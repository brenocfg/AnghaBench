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
struct perf_event {int dummy; } ;
struct bts_ctx {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bts_ctx ; 
 int /*<<< orphan*/  intel_pmu_disable_bts () ; 
 struct bts_ctx* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __bts_event_stop(struct perf_event *event, int state)
{
	struct bts_ctx *bts = this_cpu_ptr(&bts_ctx);

	/* ACTIVE -> INACTIVE(PMI)/STOPPED(->stop()) */
	WRITE_ONCE(bts->state, state);

	/*
	 * No extra synchronization is mandated by the documentation to have
	 * BTS data stores globally visible.
	 */
	intel_pmu_disable_bts();
}