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
struct pci_mv_softc {int /*<<< orphan*/ ** phy; int /*<<< orphan*/  dev; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int ENOENT ; 
 int MV_MAX_LANES ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int phy_enable (int /*<<< orphan*/ *) ; 
 int phy_get_by_ofw_idx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  phy_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pci_mv_phy_init(struct pci_mv_softc *sc)
{
	int i, rv;

	for (i = 0; i < MV_MAX_LANES; i++) {
		rv =  phy_get_by_ofw_idx(sc->dev, sc->node, i, &(sc->phy[i]));
		if (rv != 0 && rv != ENOENT) {
	  		device_printf(sc->dev, "Cannot get phy[%d]\n", i);
	  		goto fail;
	  	}
	  	if (sc->phy[i] == NULL)
	  		continue;
	  	rv = phy_enable(sc->phy[i]);
	  	if (rv != 0) {
	  		device_printf(sc->dev, "Cannot enable phy[%d]\n", i);
	  		goto fail;
	  	}
	  }
	  return (0);

fail:
	for (i = 0; i < MV_MAX_LANES; i++) {
		if (sc->phy[i] == NULL)
			continue;
		phy_release(sc->phy[i]);
	  }

	return (rv);
}