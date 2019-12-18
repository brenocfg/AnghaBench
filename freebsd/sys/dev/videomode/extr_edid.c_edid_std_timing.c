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
typedef  int uint8_t ;
struct videomode {int dummy; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 unsigned int EDID_STD_TIMING_HRES (int*) ; 
 int EDID_STD_TIMING_RATIO (int*) ; 
#define  EDID_STD_TIMING_RATIO_16_10 131 
#define  EDID_STD_TIMING_RATIO_16_9 130 
#define  EDID_STD_TIMING_RATIO_4_3 129 
#define  EDID_STD_TIMING_RATIO_5_4 128 
 unsigned int EDID_STD_TIMING_VFREQ (int*) ; 
 struct videomode* edid_mode_lookup_list (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  vesagtf_mode (unsigned int,unsigned int,unsigned int,struct videomode*) ; 

__attribute__((used)) static int
edid_std_timing(uint8_t *data, struct videomode *vmp)
{
	unsigned			x, y, f;
	const struct videomode		*lookup;
	char				name[80];

	if ((data[0] == 1 && data[1] == 1) ||
	    (data[0] == 0 && data[1] == 0) ||
	    (data[0] == 0x20 && data[1] == 0x20))
		return 0;

	x = EDID_STD_TIMING_HRES(data);
	switch (EDID_STD_TIMING_RATIO(data)) {
	case EDID_STD_TIMING_RATIO_16_10:
		y = x * 10 / 16;
		break;
	case EDID_STD_TIMING_RATIO_4_3:
		y = x * 3 / 4;
		break;
	case EDID_STD_TIMING_RATIO_5_4:
		y = x * 4 / 5;
		break;
	case EDID_STD_TIMING_RATIO_16_9:
	default:
		y = x * 9 / 16;
		break;
	}
	f = EDID_STD_TIMING_VFREQ(data);

	/* first try to lookup the mode as a DMT timing */
	snprintf(name, sizeof(name), "%dx%dx%d", x, y, f);
	if ((lookup = edid_mode_lookup_list(name)) != NULL) {
		*vmp = *lookup;
	} else {
		/* failing that, calculate it using gtf */
		/*
		 * Hmm. I'm not using alternate GTF timings, which
		 * could, in theory, be present.
		 */
		vesagtf_mode(x, y, f, vmp);
	}
	return 1;
}