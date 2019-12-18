#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int rev; } ;
struct bwn_mac {TYPE_1__ mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_B2063_COM8 ; 
 int /*<<< orphan*/  BWN_B2063_LOGEN_SP5 ; 
 int /*<<< orphan*/  BWN_B2063_PA_SP2 ; 
 int /*<<< orphan*/  BWN_B2063_PA_SP3 ; 
 int /*<<< orphan*/  BWN_B2063_PA_SP4 ; 
 int /*<<< orphan*/  BWN_B2063_PA_SP7 ; 
 int /*<<< orphan*/  BWN_B2063_REG_SP1 ; 
 int /*<<< orphan*/  BWN_B2063_RX_BB_CTL2 ; 
 int /*<<< orphan*/  BWN_B2063_TX_RF_SP6 ; 
 int /*<<< orphan*/  BWN_B2063_TX_RF_SP9 ; 
 int /*<<< orphan*/  BWN_RF_MASK (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_RF_SET (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_RF_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bwn_phy_lp_b2063_tblinit (struct bwn_mac*) ; 

__attribute__((used)) static int
bwn_phy_lp_b2063_init(struct bwn_mac *mac)
{

	bwn_phy_lp_b2063_tblinit(mac);
	BWN_RF_WRITE(mac, BWN_B2063_LOGEN_SP5, 0);
	BWN_RF_SET(mac, BWN_B2063_COM8, 0x38);
	BWN_RF_WRITE(mac, BWN_B2063_REG_SP1, 0x56);
	BWN_RF_MASK(mac, BWN_B2063_RX_BB_CTL2, ~0x2);
	BWN_RF_WRITE(mac, BWN_B2063_PA_SP7, 0);
	BWN_RF_WRITE(mac, BWN_B2063_TX_RF_SP6, 0x20);
	BWN_RF_WRITE(mac, BWN_B2063_TX_RF_SP9, 0x40);
	if (mac->mac_phy.rev == 2) {
		BWN_RF_WRITE(mac, BWN_B2063_PA_SP3, 0xa0);
		BWN_RF_WRITE(mac, BWN_B2063_PA_SP4, 0xa0);
		BWN_RF_WRITE(mac, BWN_B2063_PA_SP2, 0x18);
	} else {
		BWN_RF_WRITE(mac, BWN_B2063_PA_SP3, 0x20);
		BWN_RF_WRITE(mac, BWN_B2063_PA_SP2, 0x20);
	}

	return (0);
}