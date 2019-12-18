#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct smapi_softc {int /*<<< orphan*/ * res; scalar_t__ rid; struct smapi_bios_header* header; int /*<<< orphan*/  dev; int /*<<< orphan*/  cdev; scalar_t__ smapi32_entry; } ;
struct smapi_bios_header {int prot32_segment; char* prot32_offset; int information; int real16_segment; char* real16_offset; int prot16_segment; char* prot16_offset; int /*<<< orphan*/  checksum; int /*<<< orphan*/  length; int /*<<< orphan*/  version_minor; int /*<<< orphan*/  version_major; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 scalar_t__ BIOS_PADDRTOVADDR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int SMAPI_PROT_16BIT ; 
 int SMAPI_PROT_32BIT ; 
 int SMAPI_REAL_VM86 ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  bcd2bin (int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 struct smapi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  make_dev (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rman_get_virtual (int /*<<< orphan*/ *) ; 
 TYPE_1__ smapi_cdevsw ; 

__attribute__((used)) static int
smapi_attach (device_t dev)
{
	struct smapi_softc *sc;
	int error;

	sc = device_get_softc(dev);
	error = 0;

	sc->dev = dev;
	sc->rid = 0;
	sc->res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &sc->rid,
		 RF_ACTIVE);
	if (sc->res == NULL) {
		device_printf(dev, "Unable to allocate memory resource.\n");
		error = ENOMEM;
		goto bad;
	}
	sc->header = (struct smapi_bios_header *)rman_get_virtual(sc->res);
	sc->smapi32_entry = (u_int32_t)BIOS_PADDRTOVADDR(
					sc->header->prot32_segment +
					sc->header->prot32_offset);

        sc->cdev = make_dev(&smapi_cdevsw,
			device_get_unit(sc->dev),
			UID_ROOT, GID_WHEEL, 0600,
			"%s%d",
			smapi_cdevsw.d_name,
			device_get_unit(sc->dev));

	device_printf(dev, "Version: %d.%02d, Length: %d, Checksum: 0x%02x\n",
		bcd2bin(sc->header->version_major),
		bcd2bin(sc->header->version_minor),
		sc->header->length,
		sc->header->checksum);
	device_printf(dev, "Information=0x%b\n",
		sc->header->information,
		"\020"
		"\001REAL_VM86"
		"\002PROTECTED_16"
		"\003PROTECTED_32");

	if (bootverbose) {
		if (sc->header->information & SMAPI_REAL_VM86)
			device_printf(dev, "Real/VM86 mode: Segment 0x%04x, Offset 0x%04x\n",
				sc->header->real16_segment,
				sc->header->real16_offset);
		if (sc->header->information & SMAPI_PROT_16BIT)
			device_printf(dev, "16-bit Protected mode: Segment 0x%08x, Offset 0x%04x\n",
				sc->header->prot16_segment,
				sc->header->prot16_offset);
		if (sc->header->information & SMAPI_PROT_32BIT)
			device_printf(dev, "32-bit Protected mode: Segment 0x%08x, Offset 0x%08x\n",
				sc->header->prot32_segment,
				sc->header->prot32_offset);
	}

	return (0);
bad:
	if (sc->res)
		bus_release_resource(dev, SYS_RES_MEMORY, sc->rid, sc->res);
	return (error);
}