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
struct cfi_softc {int sc_width; int sc_cmdset; unsigned int sc_size; int /*<<< orphan*/ * sc_res; scalar_t__ sc_rid; int /*<<< orphan*/  sc_handle; int /*<<< orphan*/  sc_tag; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  desc ;

/* Variables and functions */
 scalar_t__ CFI_QRY_IDENT ; 
 scalar_t__ CFI_QRY_IFACE ; 
 scalar_t__ CFI_QRY_SIZE ; 
 scalar_t__ CFI_QRY_VEND ; 
#define  CFI_VEND_AMD_ECS 133 
#define  CFI_VEND_AMD_SCS 132 
#define  CFI_VEND_INTEL_ECS 131 
#define  CFI_VEND_INTEL_SCS 130 
#define  CFI_VEND_MITSUBISHI_ECS 129 
#define  CFI_VEND_MITSUBISHI_SCS 128 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 char* cfi_fmtsize (unsigned int) ; 
 int cfi_read_qry (struct cfi_softc*,scalar_t__) ; 
 struct cfi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

int
cfi_probe(device_t dev)
{
	char desc[80];
	struct cfi_softc *sc;
	char *vend_str;
	int error;
	uint16_t iface, vend;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	sc->sc_rid = 0;
	sc->sc_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &sc->sc_rid,
	    RF_ACTIVE);
	if (sc->sc_res == NULL)
		return (ENXIO);

	sc->sc_tag = rman_get_bustag(sc->sc_res);
	sc->sc_handle = rman_get_bushandle(sc->sc_res);

	if (sc->sc_width == 0) {
		sc->sc_width = 1;
		while (sc->sc_width <= 4) {
			if (cfi_read_qry(sc, CFI_QRY_IDENT) == 'Q')
				break;
			sc->sc_width <<= 1;
		}
	} else if (cfi_read_qry(sc, CFI_QRY_IDENT) != 'Q') {
		error = ENXIO;
		goto out;
	}
	if (sc->sc_width > 4) {
		error = ENXIO;
		goto out;
	}

	/* We got a Q. Check if we also have the R and the Y. */
	if (cfi_read_qry(sc, CFI_QRY_IDENT + 1) != 'R' ||
	    cfi_read_qry(sc, CFI_QRY_IDENT + 2) != 'Y') {
		error = ENXIO;
		goto out;
	}

	/* Get the vendor and command set. */
	vend = cfi_read_qry(sc, CFI_QRY_VEND) |
	    (cfi_read_qry(sc, CFI_QRY_VEND + 1) << 8);

	sc->sc_cmdset = vend;

	switch (vend) {
	case CFI_VEND_AMD_ECS:
	case CFI_VEND_AMD_SCS:
		vend_str = "AMD/Fujitsu";
		break;
	case CFI_VEND_INTEL_ECS:
		vend_str = "Intel/Sharp";
		break;
	case CFI_VEND_INTEL_SCS:
		vend_str = "Intel";
		break;
	case CFI_VEND_MITSUBISHI_ECS:
	case CFI_VEND_MITSUBISHI_SCS:
		vend_str = "Mitsubishi";
		break;
	default:
		vend_str = "Unknown vendor";
		break;
	}

	/* Get the device size. */
	sc->sc_size = 1U << cfi_read_qry(sc, CFI_QRY_SIZE);

	/* Sanity-check the I/F */
	iface = cfi_read_qry(sc, CFI_QRY_IFACE) |
	    (cfi_read_qry(sc, CFI_QRY_IFACE + 1) << 8);

	/*
	 * Adding 1 to iface will give us a bit-wise "switch"
	 * that allows us to test for the interface width by
	 * testing a single bit.
	 */
	iface++;

	error = (iface & sc->sc_width) ? 0 : EINVAL;
	if (error)
		goto out;

	snprintf(desc, sizeof(desc), "%s - %s", vend_str,
	    cfi_fmtsize(sc->sc_size));
	device_set_desc_copy(dev, desc);

 out:
	bus_release_resource(dev, SYS_RES_MEMORY, sc->sc_rid, sc->sc_res);
	return (error);
}