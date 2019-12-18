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
typedef  scalar_t__ vmem_addr_t ;
struct opalpci_softc {int /*<<< orphan*/ * msi_vmem; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENODEV ; 
 int MAP_IRQ (int /*<<< orphan*/ ,scalar_t__) ; 
 int M_BESTFIT ; 
 int M_WAITOK ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMEM_ADDR_MAX ; 
 int /*<<< orphan*/  VMEM_ADDR_MIN ; 
 struct opalpci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powerof2 (int) ; 
 int vmem_xalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 

__attribute__((used)) static int
opalpci_alloc_msi(device_t dev, device_t child, int count, int maxcount,
    int *irqs)
{
	struct opalpci_softc *sc;
	vmem_addr_t start;
	phandle_t xref;
	int err, i;

	sc = device_get_softc(dev);
	if (sc->msi_vmem == NULL)
		return (ENODEV);

	err = vmem_xalloc(sc->msi_vmem, count, powerof2(count), 0, 0,
	    VMEM_ADDR_MIN, VMEM_ADDR_MAX, M_BESTFIT | M_WAITOK, &start);

	if (err)
		return (err);

	xref = OF_xref_from_node(ofw_bus_get_node(dev));
	for (i = 0; i < count; i++)
		irqs[i] = MAP_IRQ(xref, start + i);

	return (0);
}