#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
struct mpt_softc {int /*<<< orphan*/  path; int /*<<< orphan*/  raid_timer; } ;
struct TYPE_5__ {scalar_t__ status; int /*<<< orphan*/  func_code; } ;
struct ccb_setasync {TYPE_2__ ccb_h; struct mpt_softc* callback_arg; int /*<<< orphan*/  callback; int /*<<< orphan*/  event_enable; } ;
struct TYPE_4__ {int /*<<< orphan*/  reply_handler; } ;
typedef  TYPE_1__ mpt_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_FOUND_DEVICE ; 
 scalar_t__ CAM_REQ_CMP ; 
 int /*<<< orphan*/  MPT_HANDLER_REPLY ; 
 int /*<<< orphan*/  MPT_LOCK (struct mpt_softc*) ; 
 int /*<<< orphan*/  MPT_UNLOCK (struct mpt_softc*) ; 
 int /*<<< orphan*/  XPT_SASYNC_CB ; 
 int /*<<< orphan*/  mpt_callout_init (struct mpt_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*) ; 
 int /*<<< orphan*/  mpt_raid_async ; 
 int /*<<< orphan*/  mpt_raid_detach (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_raid_reply_handler ; 
 int /*<<< orphan*/  mpt_raid_sysctl_attach (struct mpt_softc*) ; 
 int mpt_register_handler (struct mpt_softc*,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ *) ; 
 int mpt_spawn_raid_thread (struct mpt_softc*) ; 
 int /*<<< orphan*/  raid_handler_id ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mpt_raid_attach(struct mpt_softc *mpt)
{
	struct ccb_setasync csa;
	mpt_handler_t	 handler;
	int		 error;

	mpt_callout_init(mpt, &mpt->raid_timer);

	error = mpt_spawn_raid_thread(mpt);
	if (error != 0) {
		mpt_prt(mpt, "Unable to spawn RAID thread!\n");
		goto cleanup;
	}
 
	MPT_LOCK(mpt);
	handler.reply_handler = mpt_raid_reply_handler;
	error = mpt_register_handler(mpt, MPT_HANDLER_REPLY, handler,
				     &raid_handler_id);
	if (error != 0) {
		mpt_prt(mpt, "Unable to register RAID haandler!\n");
		goto cleanup;
	}

	xpt_setup_ccb(&csa.ccb_h, mpt->path, 5);
	csa.ccb_h.func_code = XPT_SASYNC_CB;
	csa.event_enable = AC_FOUND_DEVICE;
	csa.callback = mpt_raid_async;
	csa.callback_arg = mpt;
	xpt_action((union ccb *)&csa);
	if (csa.ccb_h.status != CAM_REQ_CMP) {
		mpt_prt(mpt, "mpt_raid_attach: Unable to register "
			"CAM async handler.\n");
	}
	MPT_UNLOCK(mpt);

	mpt_raid_sysctl_attach(mpt);
	return (0);
cleanup:
	MPT_UNLOCK(mpt);
	mpt_raid_detach(mpt);
	return (error);
}