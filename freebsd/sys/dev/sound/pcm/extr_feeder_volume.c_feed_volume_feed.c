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
typedef  int uint32_t ;
struct pcm_feeder {int /*<<< orphan*/  source; struct feed_volume_info* data; } ;
struct pcm_channel {int** volume; } ;
struct feed_volume_info {scalar_t__ state; int* matrix; int channels; int bps; int /*<<< orphan*/  (* apply ) (int*,int*,int,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  volume_class; } ;

/* Variables and functions */
 int FEEDER_FEED (int /*<<< orphan*/ ,struct pcm_channel*,int /*<<< orphan*/ *,int,void*) ; 
 scalar_t__ FEEDVOLUME_BYPASS ; 
 int SND_FXDIV (int,int) ; 
 size_t SND_VOL_C_VAL (int /*<<< orphan*/ ) ; 
 int SND_VOL_FLAT ; 
 int /*<<< orphan*/  stub1 (int*,int*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
feed_volume_feed(struct pcm_feeder *f, struct pcm_channel *c, uint8_t *b,
    uint32_t count, void *source)
{
	struct feed_volume_info *info;
	uint32_t j, align;
	int i, *vol, *matrix;
	uint8_t *dst;

	/*
	 * Fetch filter data operation.
	 */
	info = f->data;

	if (info->state == FEEDVOLUME_BYPASS)
		return (FEEDER_FEED(f->source, c, b, count, source));

	vol = c->volume[SND_VOL_C_VAL(info->volume_class)];
	matrix = info->matrix;

	/*
	 * First, let see if we really need to apply gain at all.
	 */
	j = 0;
	i = info->channels;
	do {
		if (vol[matrix[--i]] != SND_VOL_FLAT) {
			j = 1;
			break;
		}
	} while (i != 0);

	/* Nope, just bypass entirely. */
	if (j == 0)
		return (FEEDER_FEED(f->source, c, b, count, source));

	dst = b;
	align = info->bps * info->channels;

	do {
		if (count < align)
			break;

		j = SND_FXDIV(FEEDER_FEED(f->source, c, dst, count, source),
		    align);
		if (j == 0)
			break;

		info->apply(vol, matrix, info->channels, dst, j);

		j *= align;
		dst += j;
		count -= j;

	} while (count != 0);

	return (dst - b);
}