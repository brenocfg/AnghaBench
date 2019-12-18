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
struct ksz8995ma_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int KSZ8995MA_CHIP_ID ; 
 int KSZ8995MA_CHIP_ID_MASK ; 
 int /*<<< orphan*/  KSZ8995MA_CID0 ; 
 int /*<<< orphan*/  KSZ8995MA_CID1 ; 
 int KSZ8995MA_FAMILI_ID ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  bzero (struct ksz8995ma_softc*,int) ; 
 struct ksz8995ma_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 int ksz8995ma_readreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ksz8995ma_probe(device_t dev)
{
	int id0, id1;
	struct ksz8995ma_softc *sc;

	sc = device_get_softc(dev);
	bzero(sc, sizeof(*sc));

	id0 = ksz8995ma_readreg(dev, KSZ8995MA_CID0);
	id1 = ksz8995ma_readreg(dev, KSZ8995MA_CID1);
	if (bootverbose)
		device_printf(dev,"Chip Identifier Register %x %x\n", id0, id1);

	/* check Product Code */
	if (id0 != KSZ8995MA_FAMILI_ID || (id1 & KSZ8995MA_CHIP_ID_MASK) !=
	    KSZ8995MA_CHIP_ID) {
		return (ENXIO);
	}

	device_set_desc_copy(dev, "Micrel KSZ8995MA SPI switch driver");
	return (BUS_PROBE_DEFAULT);
}