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
struct ntb_softc {scalar_t__ last_ts; int /*<<< orphan*/  heartbeat_timer; int /*<<< orphan*/  lr_timer; int /*<<< orphan*/  device; } ;
typedef  scalar_t__ sbintime_t ;

/* Variables and functions */
 scalar_t__ NTB_HB_TIMEOUT ; 
 scalar_t__ atom_link_is_err (struct ntb_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,scalar_t__,void (*) (void*),struct ntb_softc*) ; 
 scalar_t__ hz ; 
 scalar_t__ intel_ntb_poll_link (struct ntb_softc*) ; 
 scalar_t__ link_is_up (struct ntb_softc*) ; 
 int /*<<< orphan*/  ntb_link_event (int /*<<< orphan*/ ) ; 
 void recover_atom_link (void*) ; 
 scalar_t__ ticks ; 

__attribute__((used)) static void
atom_link_hb(void *arg)
{
	struct ntb_softc *ntb = arg;
	sbintime_t timo, poll_ts;

	timo = NTB_HB_TIMEOUT * hz;
	poll_ts = ntb->last_ts + timo;

	/*
	 * Delay polling the link status if an interrupt was received, unless
	 * the cached link status says the link is down.
	 */
	if ((sbintime_t)ticks - poll_ts < 0 && link_is_up(ntb)) {
		timo = poll_ts - ticks;
		goto out;
	}

	if (intel_ntb_poll_link(ntb))
		ntb_link_event(ntb->device);

	if (!link_is_up(ntb) && atom_link_is_err(ntb)) {
		/* Link is down with error, proceed with recovery */
		callout_reset(&ntb->lr_timer, 0, recover_atom_link, ntb);
		return;
	}

out:
	callout_reset(&ntb->heartbeat_timer, timo, atom_link_hb, ntb);
}