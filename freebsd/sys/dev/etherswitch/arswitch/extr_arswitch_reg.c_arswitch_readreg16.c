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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int MDIO_READREG (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  arswitch_split_setpage (int /*<<< orphan*/ ,int,int*,int*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
arswitch_readreg16(device_t dev, int addr)
{
	uint16_t phy, reg;

	arswitch_split_setpage(dev, addr, &phy, &reg);
	return (MDIO_READREG(device_get_parent(dev), 0x10 | phy, reg));
}