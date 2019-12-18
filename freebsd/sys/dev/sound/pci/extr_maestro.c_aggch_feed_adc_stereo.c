#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct agg_rchinfo {int srcphys; int base; unsigned int hwptr; int buflen; scalar_t__ sink; int /*<<< orphan*/ * src; TYPE_1__* parent; } ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_4__ {int bufsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  APUREG_CURPTR ; 
 int /*<<< orphan*/  agg_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  agg_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  interleave (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,unsigned int) ; 
 unsigned int wp_rdapu (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aggch_feed_adc_stereo(struct agg_rchinfo *ch)
{
	unsigned cur, last;
	int16_t *src2;

	agg_lock(ch->parent);
	cur = wp_rdapu(ch->parent, 0, APUREG_CURPTR);
	agg_unlock(ch->parent);
	cur -= 0xffff & ((ch->srcphys - ch->base) >> 1);
	last = ch->hwptr;
	src2 = ch->src + ch->parent->bufsz/4;

	if (cur < last) {
		interleave(ch->src + last, src2 + last,
			   ch->sink + 2*last, ch->buflen/2 - last);
		interleave(ch->src, src2,
			   ch->sink, cur);
	} else if (cur > last)
		interleave(ch->src + last, src2 + last,
			   ch->sink + 2*last, cur - last);
	ch->hwptr = cur;
}