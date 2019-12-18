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
typedef  int uint32_t ;
struct pcm_feeder {struct feed_format_info* data; } ;
struct feed_format_info {int channels; int ialign; int ibps; int oalign; int obps; } ;

/* Variables and functions */
 int EINVAL ; 
#define  FEEDFORMAT_CHANNELS 128 
 int SND_CHN_MAX ; 
 int SND_CHN_MIN ; 

__attribute__((used)) static int
feed_format_set(struct pcm_feeder *f, int what, int value)
{
	struct feed_format_info *info;

	info = f->data;

	switch (what) {
	case FEEDFORMAT_CHANNELS:
		if (value < SND_CHN_MIN || value > SND_CHN_MAX)
			return (EINVAL);
		info->channels = (uint32_t)value;
		info->ialign = info->ibps * info->channels;
		info->oalign = info->obps * info->channels;
		break;
	default:
		return (EINVAL);
		break;
	}

	return (0);
}