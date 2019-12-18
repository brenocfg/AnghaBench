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
typedef  int uint16_t ;
struct bwi_rf_lo {scalar_t__ ctrl_hi; scalar_t__ ctrl_lo; } ;
struct bwi_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_PHYR_RF_LO ; 
 int /*<<< orphan*/  PHY_WRITE (struct bwi_mac*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bwi_rf_lo_write(struct bwi_mac *mac, const struct bwi_rf_lo *lo)
{
	uint16_t val;

	val = (uint8_t)lo->ctrl_lo;
	val |= ((uint8_t)lo->ctrl_hi) << 8;

	PHY_WRITE(mac, BWI_PHYR_RF_LO, val);
}