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
typedef  int uint64_t ;
typedef  int uint16_t ;
struct bwn_phy {int rev; } ;
struct bwn_mac {struct bwn_phy mac_phy; } ;

/* Variables and functions */
 int BWN_ANTAUTO0 ; 
 int BWN_ANTAUTO1 ; 
 int BWN_HF_UCODE_ANTDIV_HELPER ; 
 int /*<<< orphan*/  BWN_PHY_ADIVRELATED ; 
 int /*<<< orphan*/  BWN_PHY_ANTDWELL ; 
 int BWN_PHY_ANTDWELL_AUTODIV1 ; 
 int /*<<< orphan*/  BWN_PHY_ANTWRSETT ; 
 int BWN_PHY_ANTWRSETT_ARXDIV ; 
 int /*<<< orphan*/  BWN_PHY_BBANDCFG ; 
 int BWN_PHY_BBANDCFG_RXANT ; 
 int BWN_PHY_BBANDCFG_RXANT_SHIFT ; 
 int /*<<< orphan*/  BWN_PHY_DIVSRCHGAINBACK ; 
 int /*<<< orphan*/  BWN_PHY_OFDM61 ; 
 int BWN_PHY_OFDM61_10 ; 
 int /*<<< orphan*/  BWN_PHY_OFDM9B ; 
 int BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int bwn_hf_read (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_hf_write (struct bwn_mac*,int) ; 

void
bwn_phy_g_set_antenna(struct bwn_mac *mac, int antenna)
{
	struct bwn_phy *phy = &mac->mac_phy;
	uint64_t hf;
	int autodiv = 0;
	uint16_t tmp;

	if (antenna == BWN_ANTAUTO0 || antenna == BWN_ANTAUTO1)
		autodiv = 1;

	hf = bwn_hf_read(mac) & ~BWN_HF_UCODE_ANTDIV_HELPER;
	bwn_hf_write(mac, hf);

	BWN_PHY_WRITE(mac, BWN_PHY_BBANDCFG,
	    (BWN_PHY_READ(mac, BWN_PHY_BBANDCFG) & ~BWN_PHY_BBANDCFG_RXANT) |
	    ((autodiv ? BWN_ANTAUTO1 : antenna)
		<< BWN_PHY_BBANDCFG_RXANT_SHIFT));

	if (autodiv) {
		tmp = BWN_PHY_READ(mac, BWN_PHY_ANTDWELL);
		if (antenna == BWN_ANTAUTO1)
			tmp &= ~BWN_PHY_ANTDWELL_AUTODIV1;
		else
			tmp |= BWN_PHY_ANTDWELL_AUTODIV1;
		BWN_PHY_WRITE(mac, BWN_PHY_ANTDWELL, tmp);
	}
	tmp = BWN_PHY_READ(mac, BWN_PHY_ANTWRSETT);
	if (autodiv)
		tmp |= BWN_PHY_ANTWRSETT_ARXDIV;
	else
		tmp &= ~BWN_PHY_ANTWRSETT_ARXDIV;
	BWN_PHY_WRITE(mac, BWN_PHY_ANTWRSETT, tmp);
	if (phy->rev >= 2) {
		BWN_PHY_WRITE(mac, BWN_PHY_OFDM61,
		    BWN_PHY_READ(mac, BWN_PHY_OFDM61) | BWN_PHY_OFDM61_10);
		BWN_PHY_WRITE(mac, BWN_PHY_DIVSRCHGAINBACK,
		    (BWN_PHY_READ(mac, BWN_PHY_DIVSRCHGAINBACK) & 0xff00) |
		    0x15);
		if (phy->rev == 2)
			BWN_PHY_WRITE(mac, BWN_PHY_ADIVRELATED, 8);
		else
			BWN_PHY_WRITE(mac, BWN_PHY_ADIVRELATED,
			    (BWN_PHY_READ(mac, BWN_PHY_ADIVRELATED) & 0xff00) |
			    8);
	}
	if (phy->rev >= 6)
		BWN_PHY_WRITE(mac, BWN_PHY_OFDM9B, 0xdc);

	hf |= BWN_HF_UCODE_ANTDIV_HELPER;
	bwn_hf_write(mac, hf);
}