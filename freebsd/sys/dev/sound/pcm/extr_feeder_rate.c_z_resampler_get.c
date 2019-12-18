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
struct z_info {int rsrc; int rdst; int quality; int channels; } ;
struct pcm_feeder {struct z_info* data; } ;

/* Variables and functions */
#define  Z_RATE_CHANNELS 131 
#define  Z_RATE_DST 130 
#define  Z_RATE_QUALITY 129 
#define  Z_RATE_SRC 128 

__attribute__((used)) static int
z_resampler_get(struct pcm_feeder *f, int what)
{
	struct z_info *info;

	info = f->data;

	switch (what) {
	case Z_RATE_SRC:
		return (info->rsrc);
		break;
	case Z_RATE_DST:
		return (info->rdst);
		break;
	case Z_RATE_QUALITY:
		return (info->quality);
		break;
	case Z_RATE_CHANNELS:
		return (info->channels);
		break;
	default:
		break;
	}

	return (-1);
}