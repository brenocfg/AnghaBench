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
typedef  int uint16_t ;
struct bwn_phy {scalar_t__ type; int rf_rev; int rev; } ;
struct bwn_mac {struct bwn_phy mac_phy; } ;

/* Variables and functions */
 scalar_t__ BWN_PHYTYPE_B ; 

__attribute__((used)) static uint16_t
bwn_lo_txctl_regtable(struct bwn_mac *mac,
    uint16_t *value, uint16_t *pad_mix_gain)
{
	struct bwn_phy *phy = &mac->mac_phy;
	uint16_t reg, v, padmix;

	if (phy->type == BWN_PHYTYPE_B) {
		v = 0x30;
		if (phy->rf_rev <= 5) {
			reg = 0x43;
			padmix = 0;
		} else {
			reg = 0x52;
			padmix = 5;
		}
	} else {
		if (phy->rev >= 2 && phy->rf_rev == 8) {
			reg = 0x43;
			v = 0x10;
			padmix = 2;
		} else {
			reg = 0x52;
			v = 0x30;
			padmix = 5;
		}
	}
	if (value)
		*value = v;
	if (pad_mix_gain)
		*pad_mix_gain = padmix;

	return (reg);
}