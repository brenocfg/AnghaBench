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
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 void bwn_nphy_op_free (struct bwn_mac*) ; 

void
bwn_phy_n_detach(struct bwn_mac *mac)
{

#ifdef	BWN_GPL_PHY
	return bwn_nphy_op_free(mac);
#endif
}