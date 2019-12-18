#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct mss_info {int bd_id; } ;
typedef  TYPE_1__** mixer_tab ;
struct TYPE_6__ {scalar_t__ nbits; int regno; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 size_t LEFT_CHN ; 
#define  MD_OPTI930 129 
#define  MD_OPTI931 128 
 size_t RIGHT_CHN ; 
 int ad_read (struct mss_info*,int) ; 
 int /*<<< orphan*/  ad_write (struct mss_info*,int,int) ; 
 int /*<<< orphan*/  change_bits (TYPE_1__***,int*,int,size_t,int) ; 
 TYPE_1__** mix_devices ; 
 TYPE_1__** opti930_devices ; 
 TYPE_1__** opti931_devices ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static int
mss_mixer_set(struct mss_info *mss, int dev, int left, int right)
{
    	int        regoffs;
    	mixer_tab *mix_d;
    	u_char     old, val;

	switch (mss->bd_id) {
		case MD_OPTI931:
			mix_d = &opti931_devices;
			break;
		case MD_OPTI930:
			mix_d = &opti930_devices;
			break;
		default:
			mix_d = &mix_devices;
	}

    	if ((*mix_d)[dev][LEFT_CHN].nbits == 0) {
		DEB(printf("nbits = 0 for dev %d\n", dev));
		return -1;
    	}

    	if ((*mix_d)[dev][RIGHT_CHN].nbits == 0) right = left; /* mono */

    	/* Set the left channel */

    	regoffs = (*mix_d)[dev][LEFT_CHN].regno;
    	old = val = ad_read(mss, regoffs);
    	/* if volume is 0, mute chan. Otherwise, unmute. */
    	if (regoffs != 0) val = (left == 0)? old | 0x80 : old & 0x7f;
    	change_bits(mix_d, &val, dev, LEFT_CHN, left);
    	ad_write(mss, regoffs, val);

    	DEB(printf("LEFT: dev %d reg %d old 0x%02x new 0x%02x\n",
		dev, regoffs, old, val));

    	if ((*mix_d)[dev][RIGHT_CHN].nbits != 0) { /* have stereo */
		/* Set the right channel */
		regoffs = (*mix_d)[dev][RIGHT_CHN].regno;
		old = val = ad_read(mss, regoffs);
		if (regoffs != 1) val = (right == 0)? old | 0x80 : old & 0x7f;
		change_bits(mix_d, &val, dev, RIGHT_CHN, right);
		ad_write(mss, regoffs, val);

		DEB(printf("RIGHT: dev %d reg %d old 0x%02x new 0x%02x\n",
	    	dev, regoffs, old, val));
    	}
    	return 0; /* success */
}