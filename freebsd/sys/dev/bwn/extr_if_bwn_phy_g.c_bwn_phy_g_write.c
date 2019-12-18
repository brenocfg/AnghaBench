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

/* Variables and functions */
 int /*<<< orphan*/  BWN_PHYCTL ; 
 int /*<<< orphan*/  BWN_PHYDATA ; 
 int /*<<< orphan*/  BWN_WRITE_2 (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bwn_phy_g_write(struct bwn_mac *mac, uint16_t reg, uint16_t value)
{

	BWN_WRITE_2(mac, BWN_PHYCTL, reg);
	BWN_WRITE_2(mac, BWN_PHYDATA, value);
}