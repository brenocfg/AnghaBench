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
struct mpt_personality {int dummy; } ;

/* Variables and functions */
 size_t MPT_CBI (int /*<<< orphan*/ ) ; 
 int MPT_NUM_REPLY_HANDLERS ; 
 int /*<<< orphan*/  MPT_REPLY_HANDLER_CONFIG ; 
 int /*<<< orphan*/  MPT_REPLY_HANDLER_EVENTS ; 
 int /*<<< orphan*/  MPT_REPLY_HANDLER_HANDSHAKE ; 
 int /*<<< orphan*/  mpt_config_reply_handler ; 
 int /*<<< orphan*/  mpt_default_reply_handler ; 
 int /*<<< orphan*/  mpt_event_reply_handler ; 
 int /*<<< orphan*/  mpt_handshake_reply_handler ; 
 int /*<<< orphan*/ * mpt_reply_handlers ; 

__attribute__((used)) static int
mpt_core_load(struct mpt_personality *pers)
{
	int i;

	/*
	 * Setup core handlers and insert the default handler
	 * into all "empty slots".
	 */
	for (i = 0; i < MPT_NUM_REPLY_HANDLERS; i++) {
		mpt_reply_handlers[i] = mpt_default_reply_handler;
	}

	mpt_reply_handlers[MPT_CBI(MPT_REPLY_HANDLER_EVENTS)] =
	    mpt_event_reply_handler;
	mpt_reply_handlers[MPT_CBI(MPT_REPLY_HANDLER_CONFIG)] =
	    mpt_config_reply_handler;
	mpt_reply_handlers[MPT_CBI(MPT_REPLY_HANDLER_HANDSHAKE)] =
	    mpt_handshake_reply_handler;
	return (0);
}