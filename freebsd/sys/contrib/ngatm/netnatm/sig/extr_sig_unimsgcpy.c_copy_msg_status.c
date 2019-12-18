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
struct uni_status {int /*<<< orphan*/  unrec; int /*<<< orphan*/  epstate; int /*<<< orphan*/  epref; int /*<<< orphan*/  cause; int /*<<< orphan*/  callstate; } ;

/* Variables and functions */
 scalar_t__ IE_ISGOOD (int /*<<< orphan*/ ) ; 

void
copy_msg_status(struct uni_status *src, struct uni_status *dst)
{
	if(IE_ISGOOD(src->callstate))
		dst->callstate = src->callstate;
	if(IE_ISGOOD(src->cause))
		dst->cause = src->cause;
	if(IE_ISGOOD(src->epref))
		dst->epref = src->epref;
	if(IE_ISGOOD(src->epstate))
		dst->epstate = src->epstate;
	if(IE_ISGOOD(src->unrec))
		dst->unrec = src->unrec;
}