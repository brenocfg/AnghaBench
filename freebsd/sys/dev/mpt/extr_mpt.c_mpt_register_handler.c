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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t u_int ;
struct mpt_softc {int dummy; } ;
typedef  int mpt_handler_type ;
struct TYPE_3__ {int /*<<< orphan*/  reply_handler; } ;
typedef  TYPE_1__ mpt_handler_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MPT_CBI_TO_HID (size_t) ; 
 size_t MPT_HANDLER_ID_NONE ; 
#define  MPT_HANDLER_REPLY 128 
 size_t MPT_NUM_REPLY_HANDLERS ; 
 int /*<<< orphan*/  mpt_default_reply_handler ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*,int) ; 
 int /*<<< orphan*/ * mpt_reply_handlers ; 

int
mpt_register_handler(struct mpt_softc *mpt, mpt_handler_type type,
		     mpt_handler_t handler, uint32_t *phandler_id)
{

	switch (type) {
	case MPT_HANDLER_REPLY:
	{
		u_int cbi;
		u_int free_cbi;

		if (phandler_id == NULL)
			return (EINVAL);

		free_cbi = MPT_HANDLER_ID_NONE;
		for (cbi = 0; cbi < MPT_NUM_REPLY_HANDLERS; cbi++) {
			/*
			 * If the same handler is registered multiple
			 * times, don't error out.  Just return the
			 * index of the original registration.
			 */
			if (mpt_reply_handlers[cbi] == handler.reply_handler) {
				*phandler_id = MPT_CBI_TO_HID(cbi);
				return (0);
			}

			/*
			 * Fill from the front in the hope that
			 * all registered handlers consume only a
			 * single cache line.
			 *
			 * We don't break on the first empty slot so
			 * that the full table is checked to see if
			 * this handler was previously registered.
			 */
			if (free_cbi == MPT_HANDLER_ID_NONE &&
			    (mpt_reply_handlers[cbi]
			  == mpt_default_reply_handler))
				free_cbi = cbi;
		}
		if (free_cbi == MPT_HANDLER_ID_NONE) {
			return (ENOMEM);
		}
		mpt_reply_handlers[free_cbi] = handler.reply_handler;
		*phandler_id = MPT_CBI_TO_HID(free_cbi);
		break;
	}
	default:
		mpt_prt(mpt, "mpt_register_handler unknown type %d\n", type);
		return (EINVAL);
	}
	return (0);
}