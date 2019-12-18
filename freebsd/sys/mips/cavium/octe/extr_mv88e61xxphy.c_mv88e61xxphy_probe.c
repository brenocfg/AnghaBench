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
 int ENXIO ; 
 int MIIBUS_READREG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MV88E61XX_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MV88E61XX_PORT_REVISION ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
mv88e61xxphy_probe(device_t dev)
{
	uint16_t val;

	val = MIIBUS_READREG(device_get_parent(dev), MV88E61XX_PORT(0),
	    MV88E61XX_PORT_REVISION);
	switch (val >> 4) {
	case 0x121:
		device_set_desc(dev, "Marvell Link Street 88E6123 3-Port Gigabit Switch");
		return (0);
	case 0x161:
		device_set_desc(dev, "Marvell Link Street 88E6161 6-Port Gigabit Switch");
		return (0);
	case 0x165:
		device_set_desc(dev, "Marvell Link Street 88E6161 6-Port Advanced Gigabit Switch");
		return (0);
	default:
		return (ENXIO);
	}
}