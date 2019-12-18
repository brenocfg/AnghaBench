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
struct uni_add_party_ack {int /*<<< orphan*/  unrec; int /*<<< orphan*/  called_soft; int /*<<< orphan*/ * git; int /*<<< orphan*/  uu; int /*<<< orphan*/  connedsub; int /*<<< orphan*/  conned; int /*<<< orphan*/  eetd; int /*<<< orphan*/  notify; int /*<<< orphan*/  blli; int /*<<< orphan*/  aal; int /*<<< orphan*/  epref; } ;

/* Variables and functions */
 scalar_t__ IE_ISGOOD (int /*<<< orphan*/ ) ; 
 size_t UNI_NUM_IE_GIT ; 

void
copy_msg_add_party_ack(struct uni_add_party_ack *src, struct uni_add_party_ack *dst)
{
	u_int s, d;

	if(IE_ISGOOD(src->epref))
		dst->epref = src->epref;
	if(IE_ISGOOD(src->aal))
		dst->aal = src->aal;
	if(IE_ISGOOD(src->blli))
		dst->blli = src->blli;
	if(IE_ISGOOD(src->notify))
		dst->notify = src->notify;
	if(IE_ISGOOD(src->eetd))
		dst->eetd = src->eetd;
	if(IE_ISGOOD(src->conned))
		dst->conned = src->conned;
	if(IE_ISGOOD(src->connedsub))
		dst->connedsub = src->connedsub;
	if(IE_ISGOOD(src->uu))
		dst->uu = src->uu;
	for(s = d = 0; s < UNI_NUM_IE_GIT; s++)
		if(IE_ISGOOD(src->git[s]))
			dst->git[d++] = src->git[s];
	if(IE_ISGOOD(src->called_soft))
		dst->called_soft = src->called_soft;
	if(IE_ISGOOD(src->unrec))
		dst->unrec = src->unrec;
}