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
typedef  size_t u_int ;
struct uni_modify_ack {int /*<<< orphan*/  unrec; int /*<<< orphan*/ * git; int /*<<< orphan*/  notify; int /*<<< orphan*/  traffic; int /*<<< orphan*/  report; } ;

/* Variables and functions */
 scalar_t__ IE_ISGOOD (int /*<<< orphan*/ ) ; 
 size_t UNI_NUM_IE_GIT ; 

void
copy_msg_modify_ack(struct uni_modify_ack *src, struct uni_modify_ack *dst)
{
	u_int s, d;

	if(IE_ISGOOD(src->report))
		dst->report = src->report;
	if(IE_ISGOOD(src->traffic))
		dst->traffic = src->traffic;
	if(IE_ISGOOD(src->notify))
		dst->notify = src->notify;
	for(s = d = 0; s < UNI_NUM_IE_GIT; s++)
		if(IE_ISGOOD(src->git[s]))
			dst->git[d++] = src->git[s];
	if(IE_ISGOOD(src->unrec))
		dst->unrec = src->unrec;
}