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
typedef  int u_int ;
struct uni_release {int /*<<< orphan*/  unrec; int /*<<< orphan*/  crankback; int /*<<< orphan*/  facility; int /*<<< orphan*/  uu; int /*<<< orphan*/ * git; int /*<<< orphan*/  notify; int /*<<< orphan*/ * cause; } ;

/* Variables and functions */
 scalar_t__ IE_ISGOOD (int /*<<< orphan*/ ) ; 
 int UNI_NUM_IE_GIT ; 

void
copy_msg_release(struct uni_release *src, struct uni_release *dst)
{
	u_int s, d;

	for(s = d = 0; s < 2; s++)
		if(IE_ISGOOD(src->cause[s]))
			dst->cause[d++] = src->cause[s];
	if(IE_ISGOOD(src->notify))
		dst->notify = src->notify;
	for(s = d = 0; s < UNI_NUM_IE_GIT; s++)
		if(IE_ISGOOD(src->git[s]))
			dst->git[d++] = src->git[s];
	if(IE_ISGOOD(src->uu))
		dst->uu = src->uu;
	if(IE_ISGOOD(src->facility))
		dst->facility = src->facility;
	if(IE_ISGOOD(src->crankback))
		dst->crankback = src->crankback;
	if(IE_ISGOOD(src->unrec))
		dst->unrec = src->unrec;
}