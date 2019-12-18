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
struct uni_modify_rej {int /*<<< orphan*/  unrec; int /*<<< orphan*/ * git; int /*<<< orphan*/  notify; int /*<<< orphan*/  cause; } ;

/* Variables and functions */
 scalar_t__ IE_ISGOOD (int /*<<< orphan*/ ) ; 
 size_t UNI_NUM_IE_GIT ; 

void
copy_msg_modify_rej(struct uni_modify_rej *src, struct uni_modify_rej *dst)
{
	u_int s, d;

	if(IE_ISGOOD(src->cause))
		dst->cause = src->cause;
	if(IE_ISGOOD(src->notify))
		dst->notify = src->notify;
	for(s = d = 0; s < UNI_NUM_IE_GIT; s++)
		if(IE_ISGOOD(src->git[s]))
			dst->git[d++] = src->git[s];
	if(IE_ISGOOD(src->unrec))
		dst->unrec = src->unrec;
}