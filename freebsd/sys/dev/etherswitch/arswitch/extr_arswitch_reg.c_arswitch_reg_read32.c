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
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int MDIO_READREG (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
arswitch_reg_read32(device_t dev, int phy, int reg)
{
	uint16_t lo, hi;
	lo = MDIO_READREG(device_get_parent(dev), phy, reg);
	hi = MDIO_READREG(device_get_parent(dev), phy, reg + 1);

	return (hi << 16) | lo;
}