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
struct bwn_phy_lp {int plp_antenna; } ;
struct bwn_phy {int rev; struct bwn_phy_lp phy_lp; } ;
struct bwn_mac {struct bwn_phy mac_phy; } ;

/* Variables and functions */
 int BWN_ANTAUTO1 ; 
 int BWN_HF_UCODE_ANTDIV_HELPER ; 
 int /*<<< orphan*/  BWN_PHY_CRSGAIN_CTL ; 
 int /*<<< orphan*/  BWN_PHY_SETMASK (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 
 int bwn_hf_read (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_hf_write (struct bwn_mac*,int) ; 

void
bwn_phy_lp_set_antenna(struct bwn_mac *mac, int antenna)
{
	struct bwn_phy *phy = &mac->mac_phy;
	struct bwn_phy_lp *plp = &phy->phy_lp;

	if (phy->rev >= 2 || antenna > BWN_ANTAUTO1)
		return;

	bwn_hf_write(mac, bwn_hf_read(mac) & ~BWN_HF_UCODE_ANTDIV_HELPER);
	BWN_PHY_SETMASK(mac, BWN_PHY_CRSGAIN_CTL, 0xfffd, antenna & 0x2);
	BWN_PHY_SETMASK(mac, BWN_PHY_CRSGAIN_CTL, 0xfffe, antenna & 0x1);
	bwn_hf_write(mac, bwn_hf_read(mac) | BWN_HF_UCODE_ANTDIV_HELPER);
	plp->plp_antenna = antenna;
}