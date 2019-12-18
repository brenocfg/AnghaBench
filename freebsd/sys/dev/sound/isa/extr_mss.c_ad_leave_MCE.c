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
typedef  int u_char ;
struct mss_info {int bd_flags; } ;

/* Variables and functions */
 int BD_F_MCE_BIT ; 
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSS_INDEX ; 
 int MSS_MCE ; 
 int MSS_TRD ; 
 int /*<<< orphan*/  ad_wait_init (struct mss_info*,int) ; 
 int io_rd (struct mss_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_wr (struct mss_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  wait_for_calibration (struct mss_info*) ; 

__attribute__((used)) static void
ad_leave_MCE(struct mss_info *mss)
{
    	u_char   prev;

    	if ((mss->bd_flags & BD_F_MCE_BIT) == 0) {
		DEB(printf("--- hey, leave_MCE: MCE bit was not set!\n"));
		return;
    	}

    	ad_wait_init(mss, 1000000);

    	mss->bd_flags &= ~BD_F_MCE_BIT;

    	prev = io_rd(mss, MSS_INDEX);
    	prev &= ~MSS_TRD;
    	io_wr(mss, MSS_INDEX, prev & ~MSS_MCE); /* Clear the MCE bit */
    	wait_for_calibration(mss);
}