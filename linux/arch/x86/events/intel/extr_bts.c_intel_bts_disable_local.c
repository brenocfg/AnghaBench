#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ event; } ;
struct bts_ctx {TYPE_1__ handle; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ BTS_STATE_ACTIVE ; 
 int /*<<< orphan*/  BTS_STATE_INACTIVE ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __bts_event_stop (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bts_ctx ; 
 struct bts_ctx* this_cpu_ptr (int /*<<< orphan*/ *) ; 

void intel_bts_disable_local(void)
{
	struct bts_ctx *bts = this_cpu_ptr(&bts_ctx);

	/*
	 * Here we transition from ACTIVE to INACTIVE;
	 * do nothing for STOPPED or INACTIVE.
	 */
	if (READ_ONCE(bts->state) != BTS_STATE_ACTIVE)
		return;

	if (bts->handle.event)
		__bts_event_stop(bts->handle.event, BTS_STATE_INACTIVE);
}