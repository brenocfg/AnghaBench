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

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ MD_GUSMAX ; 
 scalar_t__ MD_GUSPNP ; 
 int MSS_IDXBUSY ; 
 int ad_read (struct mss_info*,int) ; 
 int ad_wait_init (struct mss_info*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
wait_for_calibration(struct mss_info *mss)
{
    	int t;

    	/*
     	 * Wait until the auto calibration process has finished.
     	 *
     	 * 1) Wait until the chip becomes ready (reads don't return 0x80).
     	 * 2) Wait until the ACI bit of I11 gets on
     	 * 3) Wait until the ACI bit of I11 gets off
     	 */

    	t = ad_wait_init(mss, 1000000);
    	if (t & MSS_IDXBUSY) printf("mss: Auto calibration timed out(1).\n");

	/*
	 * The calibration mode for chips that support it is set so that
	 * we never see ACI go on.
	 */
	if (mss->bd_id == MD_GUSMAX || mss->bd_id == MD_GUSPNP) {
		for (t = 100; t > 0 && (ad_read(mss, 11) & 0x20) == 0; t--);
	} else {
       		/*
		 * XXX This should only be enabled for cards that *really*
		 * need it.  Are there any?
		 */
  		for (t = 100; t > 0 && (ad_read(mss, 11) & 0x20) == 0; t--) DELAY(100);
	}
    	for (t = 100; t > 0 && ad_read(mss, 11) & 0x20; t--) DELAY(100);
}