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

/* Variables and functions */
 int /*<<< orphan*/  LP_DELAY ; 
 int LP_PINITP ; 
 int LP_PSELECP ; 
 int /*<<< orphan*/  lp_claim_parport_or_block (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lp_release_parport (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lp_table ; 
 int r_str (int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_ctr (int,int) ; 

__attribute__((used)) static int lp_reset(int minor)
{
	int retval;
	lp_claim_parport_or_block(&lp_table[minor]);
	w_ctr(minor, LP_PSELECP);
	udelay(LP_DELAY);
	w_ctr(minor, LP_PSELECP | LP_PINITP);
	retval = r_str(minor);
	lp_release_parport(&lp_table[minor]);
	return retval;
}