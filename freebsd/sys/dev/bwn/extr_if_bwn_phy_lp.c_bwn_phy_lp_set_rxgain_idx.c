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
typedef  int /*<<< orphan*/  uint16_t ;
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_TAB_2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_rxgain (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_tab_read (struct bwn_mac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bwn_phy_lp_set_rxgain_idx(struct bwn_mac *mac, uint16_t idx)
{

	bwn_phy_lp_set_rxgain(mac, bwn_tab_read(mac, BWN_TAB_2(12, idx)));
}