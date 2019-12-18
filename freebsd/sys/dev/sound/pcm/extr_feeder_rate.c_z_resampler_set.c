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
struct z_info {void* rsrc; void* rdst; void* quality; void* channels; } ;
struct pcm_feeder {struct z_info* data; } ;
typedef  void* int32_t ;

/* Variables and functions */
 int E2BIG ; 
 int EINVAL ; 
 void* SND_CHN_MAX ; 
 void* SND_CHN_MIN ; 
 void* Z_QUALITY_MAX ; 
 void* Z_QUALITY_MIN ; 
#define  Z_RATE_CHANNELS 131 
#define  Z_RATE_DST 130 
#define  Z_RATE_QUALITY 129 
#define  Z_RATE_SRC 128 
 void* feeder_rate_max ; 
 void* feeder_rate_min ; 
 int z_resampler_setup (struct pcm_feeder*) ; 

__attribute__((used)) static int
z_resampler_set(struct pcm_feeder *f, int what, int32_t value)
{
	struct z_info *info;
	int32_t oquality;

	info = f->data;

	switch (what) {
	case Z_RATE_SRC:
		if (value < feeder_rate_min || value > feeder_rate_max)
			return (E2BIG);
		if (value == info->rsrc)
			return (0);
		info->rsrc = value;
		break;
	case Z_RATE_DST:
		if (value < feeder_rate_min || value > feeder_rate_max)
			return (E2BIG);
		if (value == info->rdst)
			return (0);
		info->rdst = value;
		break;
	case Z_RATE_QUALITY:
		if (value < Z_QUALITY_MIN || value > Z_QUALITY_MAX)
			return (EINVAL);
		if (value == info->quality)
			return (0);
		/*
		 * If we failed to set the requested quality, restore
		 * the old one. We cannot afford leaving it broken since
		 * passive feeder chains like vchans never reinitialize
		 * itself.
		 */
		oquality = info->quality;
		info->quality = value;
		if (z_resampler_setup(f) == 0)
			return (0);
		info->quality = oquality;
		break;
	case Z_RATE_CHANNELS:
		if (value < SND_CHN_MIN || value > SND_CHN_MAX)
			return (EINVAL);
		if (value == info->channels)
			return (0);
		info->channels = value;
		break;
	default:
		return (EINVAL);
		break;
	}

	return (z_resampler_setup(f));
}