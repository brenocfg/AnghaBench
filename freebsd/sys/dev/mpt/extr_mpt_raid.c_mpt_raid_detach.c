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
struct TYPE_5__ {int /*<<< orphan*/  func_code; } ;
struct ccb_setasync {struct mpt_softc* callback_arg; int /*<<< orphan*/  callback; scalar_t__ event_enable; TYPE_2__ ccb_h; } ;
struct TYPE_4__ {int /*<<< orphan*/  reply_handler; } ;
typedef  TYPE_1__ mpt_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPT_HANDLER_REPLY ; 
 int /*<<< orphan*/  MPT_LOCK (struct mpt_softc*) ; 
 int /*<<< orphan*/  MPT_UNLOCK (struct mpt_softc*) ; 
 int /*<<< orphan*/  XPT_SASYNC_CB ; 
 int /*<<< orphan*/  mpt_callout_drain (struct mpt_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpt_deregister_handler (struct mpt_softc*,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_raid_async ; 
 int /*<<< orphan*/  mpt_raid_reply_handler ; 
 int /*<<< orphan*/  mpt_terminate_raid_thread (struct mpt_softc*) ; 
 int /*<<< orphan*/  raid_handler_id ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mpt_raid_detach(struct mpt_softc *mpt)
{
	struct ccb_setasync csa;
	mpt_handler_t handler;

	mpt_callout_drain(mpt, &mpt->raid_timer);

	MPT_LOCK(mpt);
	mpt_terminate_raid_thread(mpt); 
	handler.reply_handler = mpt_raid_reply_handler;
	mpt_deregister_handler(mpt, MPT_HANDLER_REPLY, handler,
			       raid_handler_id);
	xpt_setup_ccb(&csa.ccb_h, mpt->path, /*priority*/5);
	csa.ccb_h.func_code = XPT_SASYNC_CB;
	csa.event_enable = 0;
	csa.callback = mpt_raid_async;
	csa.callback_arg = mpt;
	xpt_action((union ccb *)&csa);
	MPT_UNLOCK(mpt);
}