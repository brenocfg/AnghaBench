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
struct t4iov_softc {int sc_attached; int /*<<< orphan*/  sc_main; } ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int T4_READ_PORT_DEVICE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct t4iov_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pci_get_function (int /*<<< orphan*/ ) ; 
 int pci_iov_attach_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pci_iov_schema_alloc_node () ; 

__attribute__((used)) static int
t4iov_attach_child(device_t dev)
{
	struct t4iov_softc *sc;
#ifdef PCI_IOV
	nvlist_t *pf_schema, *vf_schema;
#endif
	device_t pdev;
	int error;

	sc = device_get_softc(dev);
	MPASS(!sc->sc_attached);

	/*
	 * PF0-3 are associated with a specific port on the NIC (PF0
	 * with port 0, etc.).  Ask the PF4 driver for the device for
	 * this function's associated port to determine if the port is
	 * present.
	 */
	error = T4_READ_PORT_DEVICE(sc->sc_main, pci_get_function(dev), &pdev);
	if (error)
		return (0);

#ifdef PCI_IOV
	pf_schema = pci_iov_schema_alloc_node();
	vf_schema = pci_iov_schema_alloc_node();
	error = pci_iov_attach_name(dev, pf_schema, vf_schema, "%s",
	    device_get_nameunit(pdev));
	if (error) {
		device_printf(dev, "Failed to initialize SR-IOV: %d\n", error);
		return (0);
	}
#endif

	sc->sc_attached = true;
	return (0);
}