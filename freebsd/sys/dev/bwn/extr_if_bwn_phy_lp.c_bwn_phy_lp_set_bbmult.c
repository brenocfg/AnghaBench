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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_TAB_2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bwn_tab_write (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bwn_phy_lp_set_bbmult(struct bwn_mac *mac, uint8_t bbmult)
{

	bwn_tab_write(mac, BWN_TAB_2(0, 87), (uint16_t)bbmult << 8);
}