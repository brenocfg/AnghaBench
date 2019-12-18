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
struct arswitch_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int arswitch_reg_write32 (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  arswitch_split_setpage (int /*<<< orphan*/ ,int,int*,int*) ; 
 struct arswitch_softc* device_get_softc (int /*<<< orphan*/ ) ; 

int
arswitch_writereg(device_t dev, int addr, int value)
{
	struct arswitch_softc *sc;
	uint16_t phy, reg;

	sc = device_get_softc(dev);

	arswitch_split_setpage(dev, addr, &phy, &reg);
	return (arswitch_reg_write32(dev, 0x10 | phy, reg, value));
}