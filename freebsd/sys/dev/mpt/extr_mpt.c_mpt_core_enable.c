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
struct mpt_softc {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MPT_LOCK (struct mpt_softc*) ; 
 scalar_t__ MPT_OK ; 
 int /*<<< orphan*/  MPT_UNLOCK (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_enable_ints (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_intr (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*) ; 
 int /*<<< orphan*/  mpt_send_event_request (struct mpt_softc*,int) ; 
 scalar_t__ mpt_send_port_enable (struct mpt_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mpt_core_enable(struct mpt_softc *mpt)
{

	/*
	 * We enter with the IOC enabled, but async events
	 * not enabled, ports not enabled and interrupts
	 * not enabled.
	 */
	MPT_LOCK(mpt);

	/*
	 * Enable asynchronous event reporting- all personalities
	 * have attached so that they should be able to now field
	 * async events.
	 */
	mpt_send_event_request(mpt, 1);

	/*
	 * Catch any pending interrupts
	 *
	 * This seems to be crucial- otherwise
	 * the portenable below times out.
	 */
	mpt_intr(mpt);

	/*
	 * Enable Interrupts
	 */
	mpt_enable_ints(mpt);

	/*
	 * Catch any pending interrupts
	 *
	 * This seems to be crucial- otherwise
	 * the portenable below times out.
	 */
	mpt_intr(mpt);

	/*
	 * Enable the port.
	 */
	if (mpt_send_port_enable(mpt, 0) != MPT_OK) {
		mpt_prt(mpt, "failed to enable port 0\n");
		MPT_UNLOCK(mpt);
		return (ENXIO);
	}
	MPT_UNLOCK(mpt);
	return (0);
}