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
typedef  scalar_t__ cc_t ;

/* Variables and functions */
 void* IAC ; 
 int /*<<< orphan*/ * slc_reply_eom ; 
 int /*<<< orphan*/ * slc_replyp ; 

void
slc_add_reply(unsigned char func, unsigned char flags, cc_t value)
{
	/* A sequence of up to 6 bytes my be written for this member of the SLC
	 * suboption list by this function.  The end of negotiation command,
	 * which is written by slc_end_reply(), will require 2 additional
	 * bytes.  Do not proceed unless there is sufficient space for these
	 * items.
	 */
	if (&slc_replyp[6+2] > slc_reply_eom)
		return;
	if ((*slc_replyp++ = func) == IAC)
		*slc_replyp++ = IAC;
	if ((*slc_replyp++ = flags) == IAC)
		*slc_replyp++ = IAC;
	if ((*slc_replyp++ = (unsigned char)value) == IAC)
		*slc_replyp++ = IAC;
}