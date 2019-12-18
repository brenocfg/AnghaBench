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
struct as3722_softc {scalar_t__ chip_rev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS3722_ASIC_ID1 ; 
 int /*<<< orphan*/  AS3722_ASIC_ID2 ; 
 scalar_t__ AS3722_DEVICE_ID ; 
 int ENXIO ; 
 int RD1 (struct as3722_softc*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int
as3722_get_version(struct as3722_softc *sc)
{
	uint8_t reg;
	int rv;

	/* Verify AS3722 ID and version. */
	rv = RD1(sc, AS3722_ASIC_ID1, &reg);
	if (rv != 0)
		return (ENXIO);

	if (reg != AS3722_DEVICE_ID) {
		device_printf(sc->dev, "Invalid chip ID is 0x%x\n", reg);
		return (ENXIO);
	}

	rv = RD1(sc, AS3722_ASIC_ID2, &sc->chip_rev);
	if (rv != 0)
		return (ENXIO);

	if (bootverbose)
		device_printf(sc->dev, "AS3722 rev: 0x%x\n", sc->chip_rev);
	return (0);
}