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
struct mss_info {scalar_t__ bd_id; } ;
struct mss_chinfo {struct mss_info* parent; } ;

/* Variables and functions */
 scalar_t__ MD_AD1845 ; 
 scalar_t__ abs (int) ; 
 int /*<<< orphan*/  ad_enter_MCE (struct mss_info*) ; 
 int /*<<< orphan*/  ad_leave_MCE (struct mss_info*) ; 
 int ad_read (struct mss_info*,int) ; 
 int /*<<< orphan*/  ad_wait_init (struct mss_info*,int) ; 
 int /*<<< orphan*/  ad_write (struct mss_info*,int,int) ; 

__attribute__((used)) static int
mss_speed(struct mss_chinfo *ch, int speed)
{
    	struct mss_info *mss = ch->parent;
    	/*
     	* In the CS4231, the low 4 bits of I8 are used to hold the
     	* sample rate.  Only a fixed number of values is allowed. This
     	* table lists them. The speed-setting routines scans the table
     	* looking for the closest match. This is the only supported method.
     	*
     	* In the CS4236, there is an alternate metod (which we do not
     	* support yet) which provides almost arbitrary frequency setting.
     	* In the AD1845, it looks like the sample rate can be
     	* almost arbitrary, and written directly to a register.
     	* In the OPTi931, there is a SB command which provides for
     	* almost arbitrary frequency setting.
     	*
     	*/
    	ad_enter_MCE(mss);
    	if (mss->bd_id == MD_AD1845) { /* Use alternate speed select regs */
		ad_write(mss, 22, (speed >> 8) & 0xff);	/* Speed MSB */
		ad_write(mss, 23, speed & 0xff);	/* Speed LSB */
		/* XXX must also do something in I27 for the ad1845 */
    	} else {
        	int i, sel = 0; /* assume entry 0 does not contain -1 */
        	static int speeds[] =
      	    	{8000, 5512, 16000, 11025, 27429, 18900, 32000, 22050,
	    	-1, 37800, -1, 44100, 48000, 33075, 9600, 6615};

        	for (i = 1; i < 16; i++)
   		    	if (speeds[i] > 0 &&
			    abs(speed-speeds[i]) < abs(speed-speeds[sel])) sel = i;
        	speed = speeds[sel];
        	ad_write(mss, 8, (ad_read(mss, 8) & 0xf0) | sel);
		ad_wait_init(mss, 10000);
    	}
    	ad_leave_MCE(mss);

    	return speed;
}