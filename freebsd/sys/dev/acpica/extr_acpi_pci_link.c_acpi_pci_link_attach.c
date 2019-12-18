#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct link_res_request {scalar_t__ count; struct acpi_pci_link_softc* sc; scalar_t__ res_index; scalar_t__ link_index; void* in_dpf; } ;
struct link_count_request {scalar_t__ count; struct acpi_pci_link_softc* sc; scalar_t__ res_index; scalar_t__ link_index; void* in_dpf; } ;
struct link {int dummy; } ;
struct acpi_pci_link_softc {scalar_t__ pl_num_links; TYPE_1__* pl_links; scalar_t__ pl_crs_bad; int /*<<< orphan*/  pl_dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int l_res_index; struct TYPE_4__* l_irqs; int /*<<< orphan*/  l_routed; void* l_irq; void* l_initial_irq; int /*<<< orphan*/  l_isa_irq; struct acpi_pci_link_softc* l_sc; void* l_bios_irq; } ;
typedef  scalar_t__ ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_SERIAL_BEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_END (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 scalar_t__ AE_NOT_FOUND ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiFormatException (scalar_t__) ; 
 scalar_t__ AcpiWalkResources (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct link_res_request*) ; 
 void* DPF_OUTSIDE ; 
 int ENXIO ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  M_PCI_LINK ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ PCI_INTERRUPT_VALID (void*) ; 
 void* PCI_INVALID_IRQ ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_count_irq_resources ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_pci_link_dump (struct acpi_pci_link_softc*,int,char*) ; 
 scalar_t__ bootverbose ; 
 struct acpi_pci_link_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_add_crs ; 
 int /*<<< orphan*/  link_add_prs ; 
 int /*<<< orphan*/  link_valid_irq (TYPE_1__*,void*) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_link ; 

__attribute__((used)) static int
acpi_pci_link_attach(device_t dev)
{
	struct acpi_pci_link_softc *sc;
	struct link_count_request creq;
	struct link_res_request rreq;
	ACPI_STATUS status;
	int i;

	sc = device_get_softc(dev);
	sc->pl_dev = dev;
	ACPI_SERIAL_BEGIN(pci_link);

	/*
	 * Count the number of current resources so we know how big of
	 * a link array to allocate.  On some systems, _CRS is broken,
	 * so for those systems try to derive the count from _PRS instead.
	 */
	creq.in_dpf = DPF_OUTSIDE;
	creq.count = 0;
	status = AcpiWalkResources(acpi_get_handle(dev), "_CRS",
	    acpi_count_irq_resources, &creq);
	sc->pl_crs_bad = ACPI_FAILURE(status);
	if (sc->pl_crs_bad) {
		creq.in_dpf = DPF_OUTSIDE;
		creq.count = 0;
		status = AcpiWalkResources(acpi_get_handle(dev), "_PRS",
		    acpi_count_irq_resources, &creq);
		if (ACPI_FAILURE(status)) {
			device_printf(dev,
			    "Unable to parse _CRS or _PRS: %s\n",
			    AcpiFormatException(status));
			ACPI_SERIAL_END(pci_link);
			return (ENXIO);
		}
	}
	sc->pl_num_links = creq.count;
	if (creq.count == 0) {
		ACPI_SERIAL_END(pci_link);
		return (0);
	}
	sc->pl_links = malloc(sizeof(struct link) * sc->pl_num_links,
	    M_PCI_LINK, M_WAITOK | M_ZERO);

	/* Initialize the child links. */
	for (i = 0; i < sc->pl_num_links; i++) {
		sc->pl_links[i].l_irq = PCI_INVALID_IRQ;
		sc->pl_links[i].l_bios_irq = PCI_INVALID_IRQ;
		sc->pl_links[i].l_sc = sc;
		sc->pl_links[i].l_isa_irq = FALSE;
		sc->pl_links[i].l_res_index = -1;
	}

	/* Try to read the current settings from _CRS if it is valid. */
	if (!sc->pl_crs_bad) {
		rreq.in_dpf = DPF_OUTSIDE;
		rreq.link_index = 0;
		rreq.res_index = 0;
		rreq.sc = sc;
		status = AcpiWalkResources(acpi_get_handle(dev), "_CRS",
		    link_add_crs, &rreq);
		if (ACPI_FAILURE(status)) {
			device_printf(dev, "Unable to parse _CRS: %s\n",
			    AcpiFormatException(status));
			goto fail;
		}
	}

	/*
	 * Try to read the possible settings from _PRS.  Note that if the
	 * _CRS is toast, we depend on having a working _PRS.  However, if
	 * _CRS works, then it is ok for _PRS to be missing.
	 */
	rreq.in_dpf = DPF_OUTSIDE;
	rreq.link_index = 0;
	rreq.res_index = 0;
	rreq.sc = sc;
	status = AcpiWalkResources(acpi_get_handle(dev), "_PRS",
	    link_add_prs, &rreq);
	if (ACPI_FAILURE(status) &&
	    (status != AE_NOT_FOUND || sc->pl_crs_bad)) {
		device_printf(dev, "Unable to parse _PRS: %s\n",
		    AcpiFormatException(status));
		goto fail;
	}
	if (bootverbose)
		acpi_pci_link_dump(sc, 1, "Initial Probe");

	/* Verify initial IRQs if we have _PRS. */
	if (status != AE_NOT_FOUND)
		for (i = 0; i < sc->pl_num_links; i++)
			if (!link_valid_irq(&sc->pl_links[i],
			    sc->pl_links[i].l_irq))
				sc->pl_links[i].l_irq = PCI_INVALID_IRQ;
	if (bootverbose)
		acpi_pci_link_dump(sc, 0, "Validation");

	/* Save initial IRQs. */
	for (i = 0; i < sc->pl_num_links; i++)
		sc->pl_links[i].l_initial_irq = sc->pl_links[i].l_irq;

	/*
	 * Try to disable this link.  If successful, set the current IRQ to
	 * zero and flags to indicate this link is not routed.  If we can't
	 * run _DIS (i.e., the method doesn't exist), assume the initial
	 * IRQ was routed by the BIOS.
	 */
	if (ACPI_SUCCESS(AcpiEvaluateObject(acpi_get_handle(dev), "_DIS", NULL,
	    NULL)))
		for (i = 0; i < sc->pl_num_links; i++)
			sc->pl_links[i].l_irq = PCI_INVALID_IRQ;
	else
		for (i = 0; i < sc->pl_num_links; i++)
			if (PCI_INTERRUPT_VALID(sc->pl_links[i].l_irq))
				sc->pl_links[i].l_routed = TRUE;
	if (bootverbose)
		acpi_pci_link_dump(sc, 0, "After Disable");
	ACPI_SERIAL_END(pci_link);
	return (0);
fail:
	ACPI_SERIAL_END(pci_link);
	for (i = 0; i < sc->pl_num_links; i++)
		if (sc->pl_links[i].l_irqs != NULL)
			free(sc->pl_links[i].l_irqs, M_PCI_LINK);
	free(sc->pl_links, M_PCI_LINK);
	return (ENXIO);
}