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
typedef  int /*<<< orphan*/  uint8_t ;
struct dc_softc {scalar_t__ dc_romwidth; int /*<<< orphan*/ * dc_srom; int /*<<< orphan*/ * dc_dev; int /*<<< orphan*/ * dc_eaddr; } ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/  devclass_t ;

/* Variables and functions */
 scalar_t__ DC_IS_INTEL (struct dc_softc*) ; 
 int /*<<< orphan*/  DC_ROM_SIZE (scalar_t__) ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int) ; 
 int devclass_get_maxunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ *) ; 
 scalar_t__ device_get_parent (int /*<<< orphan*/ *) ; 
 struct dc_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int device_get_unit (int /*<<< orphan*/ *) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dc_check_multiport(struct dc_softc *sc)
{
	struct dc_softc *dsc;
	devclass_t dc;
	device_t child;
	uint8_t *eaddr;
	int unit;

	dc = devclass_find("dc");
	for (unit = 0; unit < devclass_get_maxunit(dc); unit++) {
		child = devclass_get_device(dc, unit);
		if (child == NULL)
			continue;
		if (child == sc->dc_dev)
			continue;
		if (device_get_parent(child) != device_get_parent(sc->dc_dev))
			continue;
		if (unit > device_get_unit(sc->dc_dev))
			continue;
		if (device_is_attached(child) == 0)
			continue;
		dsc = device_get_softc(child);
		device_printf(sc->dc_dev,
		    "Using station address of %s as base\n",
		    device_get_nameunit(child));
		bcopy(dsc->dc_eaddr, sc->dc_eaddr, ETHER_ADDR_LEN);
		eaddr = (uint8_t *)sc->dc_eaddr;
		eaddr[5]++;
		/* Prepare SROM to parse again. */
		if (DC_IS_INTEL(sc) && dsc->dc_srom != NULL &&
		    sc->dc_romwidth != 0) {
			free(sc->dc_srom, M_DEVBUF);
			sc->dc_romwidth = dsc->dc_romwidth;
			sc->dc_srom = malloc(DC_ROM_SIZE(sc->dc_romwidth),
			    M_DEVBUF, M_NOWAIT);
			if (sc->dc_srom == NULL) {
				device_printf(sc->dc_dev,
				    "Could not allocate SROM buffer\n");
				return (ENOMEM);
			}
			bcopy(dsc->dc_srom, sc->dc_srom,
			    DC_ROM_SIZE(sc->dc_romwidth));
		}
		return (0);
	}
	return (ENOENT);
}