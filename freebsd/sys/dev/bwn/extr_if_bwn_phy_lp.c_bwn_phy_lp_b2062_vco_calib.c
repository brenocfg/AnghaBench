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
 int /*<<< orphan*/  BWN_B2062_S_RFPLLCTL21 ; 
 int /*<<< orphan*/  BWN_RF_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 

__attribute__((used)) static void
bwn_phy_lp_b2062_vco_calib(struct bwn_mac *mac)
{

	BWN_RF_WRITE(mac, BWN_B2062_S_RFPLLCTL21, 0x42);
	BWN_RF_WRITE(mac, BWN_B2062_S_RFPLLCTL21, 0x62);
	DELAY(200);
}