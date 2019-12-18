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
typedef  int u_int32_t ;
struct mss_info {int dummy; } ;
struct mss_chinfo {int fmt; struct mss_info* parent; } ;

/* Variables and functions */
#define  AFMT_A_LAW 133 
 int AFMT_CHANNEL (int) ; 
 int AFMT_ENCODING (int) ; 
#define  AFMT_IMA_ADPCM 132 
#define  AFMT_MU_LAW 131 
#define  AFMT_S16_LE 130 
#define  AFMT_U16_BE 129 
#define  AFMT_U8 128 
 int /*<<< orphan*/  ad_enter_MCE (struct mss_info*) ; 
 int /*<<< orphan*/  ad_leave_MCE (struct mss_info*) ; 
 int ad_read (struct mss_info*,int) ; 
 int /*<<< orphan*/  ad_wait_init (struct mss_info*,int) ; 
 int /*<<< orphan*/  ad_write (struct mss_info*,int,int) ; 

__attribute__((used)) static int
mss_format(struct mss_chinfo *ch, u_int32_t format)
{
    	struct mss_info *mss = ch->parent;
    	int i, arg = AFMT_ENCODING(format);

    	/*
     	* The data format uses 3 bits (just 2 on the 1848). For each
     	* bit setting, the following array returns the corresponding format.
     	* The code scans the array looking for a suitable format. In
     	* case it is not found, default to AFMT_U8 (not such a good
     	* choice, but let's do it for compatibility...).
     	*/

    	static int fmts[] =
        	{AFMT_U8, AFMT_MU_LAW, AFMT_S16_LE, AFMT_A_LAW,
		-1, AFMT_IMA_ADPCM, AFMT_U16_BE, -1};

	ch->fmt = format;
    	for (i = 0; i < 8; i++) if (arg == fmts[i]) break;
    	arg = i << 1;
    	if (AFMT_CHANNEL(format) > 1) arg |= 1;
    	arg <<= 4;
    	ad_enter_MCE(mss);
    	ad_write(mss, 8, (ad_read(mss, 8) & 0x0f) | arg);
	ad_wait_init(mss, 10000);
    	if (ad_read(mss, 12) & 0x40) {	/* mode2? */
		ad_write(mss, 28, arg); /* capture mode */
		ad_wait_init(mss, 10000);
	}
    	ad_leave_MCE(mss);
    	return format;
}