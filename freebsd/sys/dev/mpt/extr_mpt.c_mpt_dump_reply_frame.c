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
typedef  int /*<<< orphan*/  MSG_DEFAULT_REPLY ;

/* Variables and functions */
 int /*<<< orphan*/  mpt_print_reply (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*) ; 

void
mpt_dump_reply_frame(struct mpt_softc *mpt, MSG_DEFAULT_REPLY *reply_frame)
{

	mpt_prt(mpt, "Address Reply:\n");
	mpt_print_reply(reply_frame);
}