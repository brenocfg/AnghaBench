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
struct mss_info {int /*<<< orphan*/  bd_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD_F_MCE_BIT ; 
 int /*<<< orphan*/  MSS_INDEX ; 
 int MSS_MCE ; 
 int MSS_TRD ; 
 int /*<<< orphan*/  ad_wait_init (struct mss_info*,int) ; 
 int io_rd (struct mss_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_wr (struct mss_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ad_enter_MCE(struct mss_info *mss)
{
    	int prev;

    	mss->bd_flags |= BD_F_MCE_BIT;
    	ad_wait_init(mss, 203000);
    	prev = io_rd(mss, MSS_INDEX);
    	prev &= ~MSS_TRD;
    	io_wr(mss, MSS_INDEX, prev | MSS_MCE);
}