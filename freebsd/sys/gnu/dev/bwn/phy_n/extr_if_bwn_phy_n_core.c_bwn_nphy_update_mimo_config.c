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
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_NPHY_MIMOCFG ; 
 int /*<<< orphan*/  BWN_NPHY_MIMOCFG_AUTO ; 
 int /*<<< orphan*/  BWN_NPHY_MIMOCFG_GFMIX ; 
 int /*<<< orphan*/  BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bwn_nphy_update_mimo_config(struct bwn_mac *mac, int32_t preamble)
{
	uint16_t mimocfg = BWN_PHY_READ(mac, BWN_NPHY_MIMOCFG);

	mimocfg |= BWN_NPHY_MIMOCFG_AUTO;
	if (preamble == 1)
		mimocfg |= BWN_NPHY_MIMOCFG_GFMIX;
	else
		mimocfg &= ~BWN_NPHY_MIMOCFG_GFMIX;

	BWN_PHY_WRITE(mac, BWN_NPHY_MIMOCFG, mimocfg);
}