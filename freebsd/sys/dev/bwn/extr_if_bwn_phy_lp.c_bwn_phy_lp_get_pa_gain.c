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
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_PHY_OFDM (int) ; 
 int BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint16_t
bwn_phy_lp_get_pa_gain(struct bwn_mac *mac)
{

	return BWN_PHY_READ(mac, BWN_PHY_OFDM(0xfb)) & 0x7f;
}