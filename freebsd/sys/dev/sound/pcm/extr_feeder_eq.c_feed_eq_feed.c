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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct pcm_feeder {int /*<<< orphan*/  source; struct feed_eq_info* data; } ;
struct pcm_channel {int dummy; } ;
struct feed_eq_info {scalar_t__ state; scalar_t__ align; int /*<<< orphan*/  (* biquad ) (struct feed_eq_info*,int /*<<< orphan*/ *,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ FEEDEQ_BYPASS ; 
 int FEEDER_FEED (int /*<<< orphan*/ ,struct pcm_channel*,int /*<<< orphan*/ *,scalar_t__,void*) ; 
 scalar_t__ SND_FXDIV (int,scalar_t__) ; 
 scalar_t__ SND_FXROUND (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct feed_eq_info*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
feed_eq_feed(struct pcm_feeder *f, struct pcm_channel *c, uint8_t *b,
    uint32_t count, void *source)
{
	struct feed_eq_info *info;
	uint32_t j;
	uint8_t *dst;

	info = f->data;

	/*
	 * 3 major states:
	 * 	FEEDEQ_BYPASS  - Bypass entirely, nothing happened.
	 *      FEEDEQ_ENABLE  - Preamp+biquad filtering.
	 *      FEEDEQ_DISABLE - Preamp only.
	 */
	if (info->state == FEEDEQ_BYPASS)
		return (FEEDER_FEED(f->source, c, b, count, source));

	dst = b;
	count = SND_FXROUND(count, info->align);

	do {
		if (count < info->align)
			break;

		j = SND_FXDIV(FEEDER_FEED(f->source, c, dst, count, source),
		    info->align);
		if (j == 0)
			break;

		info->biquad(info, dst, j);

		j *= info->align;
		dst += j;
		count -= j;

	} while (count != 0);

	return (dst - b);
}