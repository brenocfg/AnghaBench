#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mpt_softc {int /*<<< orphan*/  cdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  reply_handler; } ;
typedef  TYPE_1__ mpt_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPT_HANDLER_REPLY ; 
 int /*<<< orphan*/  MPT_LOCK (struct mpt_softc*) ; 
 int /*<<< orphan*/  MPT_UNLOCK (struct mpt_softc*) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_deregister_handler (struct mpt_softc*,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_user_reply_handler ; 
 int /*<<< orphan*/  user_handler_id ; 

__attribute__((used)) static void
mpt_user_detach(struct mpt_softc *mpt)
{
	mpt_handler_t handler;

	/* XXX: do a purge of pending requests? */
	destroy_dev(mpt->cdev);

	MPT_LOCK(mpt);
	handler.reply_handler = mpt_user_reply_handler;
	mpt_deregister_handler(mpt, MPT_HANDLER_REPLY, handler,
	    user_handler_id);
	MPT_UNLOCK(mpt);
}