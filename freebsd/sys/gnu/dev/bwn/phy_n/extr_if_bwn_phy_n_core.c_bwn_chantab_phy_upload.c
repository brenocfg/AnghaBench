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
struct bwn_phy_n_sfo_cfg {int /*<<< orphan*/  phy_bw6; int /*<<< orphan*/  phy_bw5; int /*<<< orphan*/  phy_bw4; int /*<<< orphan*/  phy_bw3; int /*<<< orphan*/  phy_bw2; int /*<<< orphan*/  phy_bw1a; } ;
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_NPHY_BW1A ; 
 int /*<<< orphan*/  BWN_NPHY_BW2 ; 
 int /*<<< orphan*/  BWN_NPHY_BW3 ; 
 int /*<<< orphan*/  BWN_NPHY_BW4 ; 
 int /*<<< orphan*/  BWN_NPHY_BW5 ; 
 int /*<<< orphan*/  BWN_NPHY_BW6 ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bwn_chantab_phy_upload(struct bwn_mac *mac,
				   const struct bwn_phy_n_sfo_cfg *e)
{
	BWN_PHY_WRITE(mac, BWN_NPHY_BW1A, e->phy_bw1a);
	BWN_PHY_WRITE(mac, BWN_NPHY_BW2, e->phy_bw2);
	BWN_PHY_WRITE(mac, BWN_NPHY_BW3, e->phy_bw3);
	BWN_PHY_WRITE(mac, BWN_NPHY_BW4, e->phy_bw4);
	BWN_PHY_WRITE(mac, BWN_NPHY_BW5, e->phy_bw5);
	BWN_PHY_WRITE(mac, BWN_NPHY_BW6, e->phy_bw6);
}