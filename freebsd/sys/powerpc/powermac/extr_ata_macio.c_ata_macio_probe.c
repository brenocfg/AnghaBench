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
struct ata_macio_softc {int rev; int /*<<< orphan*/  max_mode; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_UDMA4 ; 
 int /*<<< orphan*/  ATA_WDMA2 ; 
 int ENXIO ; 
 int ata_probe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct ata_macio_softc*,int) ; 
 struct ata_macio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 char* ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 char* ofw_bus_get_type (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
ata_macio_probe(device_t dev)
{
	const char *type = ofw_bus_get_type(dev);
	const char *name = ofw_bus_get_name(dev);
	struct ata_macio_softc *sc;

	if (strcmp(type, "ata") != 0 &&
	    strcmp(type, "ide") != 0)
		return (ENXIO);

	sc = device_get_softc(dev);
	bzero(sc, sizeof(struct ata_macio_softc));

	if (strcmp(name,"ata-4") == 0) {
		device_set_desc(dev,"Apple MacIO Ultra ATA Controller");
		sc->rev = 4;
		sc->max_mode = ATA_UDMA4;
	} else {
		device_set_desc(dev,"Apple MacIO ATA Controller");
		sc->rev = 3;
		sc->max_mode = ATA_WDMA2;
	}

	return (ata_probe(dev));
}