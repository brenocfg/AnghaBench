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
typedef  int uint8_t ;
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_TAB_2 (int /*<<< orphan*/ ,int) ; 
 int bwn_tab_read (struct bwn_mac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t
bwn_phy_lp_get_bbmult(struct bwn_mac *mac)
{

	return (bwn_tab_read(mac, BWN_TAB_2(0, 87)) & 0xff00) >> 8;
}