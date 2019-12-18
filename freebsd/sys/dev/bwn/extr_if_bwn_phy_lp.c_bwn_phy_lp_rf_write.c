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
 int /*<<< orphan*/  BWN_RFCTL ; 
 int /*<<< orphan*/  BWN_RFDATALO ; 
 int /*<<< orphan*/  BWN_WRITE_2 (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 

void
bwn_phy_lp_rf_write(struct bwn_mac *mac, uint16_t reg, uint16_t value)
{

	KASSERT(reg != 1, ("unaccessible register %d", reg));
	BWN_WRITE_2(mac, BWN_RFCTL, reg);
	BWN_WRITE_2(mac, BWN_RFDATALO, value);
}