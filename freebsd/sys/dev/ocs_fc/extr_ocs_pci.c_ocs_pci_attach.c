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
struct ocs_softc {int instance_index; int /*<<< orphan*/  hw_war_version; int /*<<< orphan*/  ramlog; int /*<<< orphan*/  fc_type; int /*<<< orphan*/  dev; int /*<<< orphan*/  ocs_xport; int /*<<< orphan*/  dmat; int /*<<< orphan*/  businfo; int /*<<< orphan*/  pci_device; int /*<<< orphan*/  pci_vendor; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ARRAY_SIZE (struct ocs_softc**) ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE ; 
 int /*<<< orphan*/  BUS_SPACE_UNRESTRICTED ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  FC_TYPE_FCP ; 
 int /*<<< orphan*/  M_OCS ; 
 int /*<<< orphan*/  OCS_XPORT_FC ; 
 int /*<<< orphan*/  PCIC_SERIALBUS ; 
 scalar_t__ PCIS_SERIALBUS_FC ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ocs_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocs_debug_attach (struct ocs_softc*) ; 
 scalar_t__ ocs_device_attach (struct ocs_softc*) ; 
 int /*<<< orphan*/  ocs_device_lock_free (struct ocs_softc*) ; 
 struct ocs_softc** ocs_devices ; 
 scalar_t__ ocs_intr_alloc (struct ocs_softc*) ; 
 scalar_t__ ocs_map_bars (int /*<<< orphan*/ ,struct ocs_softc*) ; 
 int /*<<< orphan*/  ocs_ramlog_free (struct ocs_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_release_bus (struct ocs_softc*) ; 
 scalar_t__ ocs_setup_params (struct ocs_softc*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_get_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_device (int /*<<< orphan*/ ) ; 
 int pci_get_function (int /*<<< orphan*/ ) ; 
 int pci_get_slot (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subclass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_vendor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int) ; 

__attribute__((used)) static int
ocs_pci_attach(device_t dev)
{
	struct ocs_softc	*ocs;
	int			instance;

	instance = device_get_unit(dev);
	
	ocs = (struct ocs_softc *)device_get_softc(dev);
	if (NULL == ocs) {
		device_printf(dev, "cannot allocate softc\n");
		return ENOMEM;
	}
	memset(ocs, 0, sizeof(struct ocs_softc));

	if (instance < ARRAY_SIZE(ocs_devices)) {
		ocs_devices[instance] = ocs;
	} else {
		device_printf(dev, "got unexpected ocs instance number %d\n", instance);
	}

	ocs->instance_index = instance;

	ocs->dev = dev;

	pci_enable_io(dev, SYS_RES_MEMORY);
	pci_enable_busmaster(dev);

	ocs->pci_vendor = pci_get_vendor(dev);
	ocs->pci_device = pci_get_device(dev);
	snprintf(ocs->businfo, sizeof(ocs->businfo), "%02X:%02X:%02X",
		pci_get_bus(dev), pci_get_slot(dev), pci_get_function(dev));

	/* Map all memory BARs */
        if (ocs_map_bars(dev, ocs)) {
		device_printf(dev, "Failed to map pci bars\n");
		goto release_bus;
        }
	
	/* create a root DMA tag for the device */
	if (bus_dma_tag_create(bus_get_dma_tag(dev),
				1,		/* byte alignment */
				0,		/* no boundary restrictions */
				BUS_SPACE_MAXADDR, /* no minimum low address */
				BUS_SPACE_MAXADDR, /* no maximum high address */
				NULL,		/* no filter function */
				NULL,		/* or arguments */
				BUS_SPACE_MAXSIZE, /* max size covered by tag */
				BUS_SPACE_UNRESTRICTED, /* no segment count restrictions */
				BUS_SPACE_MAXSIZE, /* no segment length restrictions */
				0,		/* flags */
				NULL,		/* no lock manipulation function */
				NULL,		/* or arguments */
				&ocs->dmat)) {
		device_printf(dev, "parent DMA tag allocation failed\n");
		goto release_bus;
	}

	if (ocs_intr_alloc(ocs)) {
		device_printf(dev, "Interrupt allocation failed\n");
		goto release_bus;
	}

	if (PCIC_SERIALBUS == pci_get_class(dev) &&
			PCIS_SERIALBUS_FC == pci_get_subclass(dev))
		ocs->ocs_xport = OCS_XPORT_FC;
	else {
		device_printf(dev, "unsupported class (%#x : %#x)\n",
				pci_get_class(dev),
				pci_get_class(dev));
		goto release_bus;
	}

	/* Setup tunable parameters */
	if (ocs_setup_params(ocs)) {
		device_printf(ocs->dev, "failed to setup params\n");
		goto release_bus;
	}

	if (ocs_device_attach(ocs)) {
		device_printf(ocs->dev, "failed to attach device\n");
		goto release_params;
	}

	ocs->fc_type = FC_TYPE_FCP;

	ocs_debug_attach(ocs);

	return 0;

release_params:
	ocs_ramlog_free(ocs, ocs->ramlog);
	ocs_device_lock_free(ocs);
	free(ocs->hw_war_version, M_OCS);
release_bus:
	ocs_release_bus(ocs);
	return ENXIO;
}