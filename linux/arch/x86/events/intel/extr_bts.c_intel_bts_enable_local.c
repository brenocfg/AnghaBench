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
 int BTS_STATE_ACTIVE ; 
 int BTS_STATE_STOPPED ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __bts_event_start (scalar_t__) ; 
 int /*<<< orphan*/  bts_ctx ; 
 struct bts_ctx* this_cpu_ptr (int /*<<< orphan*/ *) ; 

void intel_bts_enable_local(void)
{
	struct bts_ctx *bts = this_cpu_ptr(&bts_ctx);
	int state = READ_ONCE(bts->state);

	/*
	 * Here we transition from INACTIVE to ACTIVE;
	 * if we instead are STOPPED from the interrupt handler,
	 * stay that way. Can't be ACTIVE here though.
	 */
	if (WARN_ON_ONCE(state == BTS_STATE_ACTIVE))
		return;

	if (state == BTS_STATE_STOPPED)
		return;

	if (bts->handle.event)
		__bts_event_start(bts->handle.event);
}