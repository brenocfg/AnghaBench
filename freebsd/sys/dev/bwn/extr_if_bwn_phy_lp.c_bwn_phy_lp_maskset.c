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
 int /*<<< orphan*/  BWN_PHYCTL ; 
 int /*<<< orphan*/  BWN_PHYDATA ; 
 int BWN_READ_2 (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_WRITE_2 (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 

void
bwn_phy_lp_maskset(struct bwn_mac *mac, uint16_t reg, uint16_t mask,
    uint16_t set)
{

	BWN_WRITE_2(mac, BWN_PHYCTL, reg);
	BWN_WRITE_2(mac, BWN_PHYDATA,
	    (BWN_READ_2(mac, BWN_PHYDATA) & mask) | set);
}