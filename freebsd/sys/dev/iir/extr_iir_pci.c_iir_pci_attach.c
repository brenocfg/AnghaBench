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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ u_int8_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct resource {int dummy; } ;
struct gdt_softc {int sc_ic_all_size; int /*<<< orphan*/  sc_lock; struct resource* sc_dpmem; scalar_t__ sc_init_level; int /*<<< orphan*/  sc_parent_dmat; int /*<<< orphan*/  sc_test_busy; int /*<<< orphan*/  sc_set_sema0; int /*<<< orphan*/  sc_release_event; int /*<<< orphan*/  sc_intr; int /*<<< orphan*/  sc_get_status; int /*<<< orphan*/  sc_copy_cmd; int /*<<< orphan*/  sc_class; int /*<<< orphan*/  sc_subdevice; int /*<<< orphan*/  sc_device; int /*<<< orphan*/  sc_vendor; int /*<<< orphan*/  sc_slot; int /*<<< orphan*/  sc_bus; int /*<<< orphan*/  sc_hanum; int /*<<< orphan*/  sc_devnode; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_UNRESTRICTED ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENOMEM ; 
 int ENXIO ; 
 scalar_t__ GDT_CMD_INDEX ; 
 scalar_t__ GDT_EDOOR_EN ; 
 int /*<<< orphan*/  GDT_I960_SZ ; 
 int /*<<< orphan*/  GDT_MPR ; 
 scalar_t__ GDT_MPR_EDOOR ; 
 scalar_t__ GDT_MPR_IC ; 
 scalar_t__ GDT_MPR_LDOOR ; 
 int GDT_MPR_MAGIC ; 
 int GDT_MPR_SZ ; 
 scalar_t__ GDT_PROTOCOL_VERSION ; 
 int GDT_RETRIES ; 
 scalar_t__ GDT_S_CMD_INDX ; 
 scalar_t__ GDT_S_INFO ; 
 scalar_t__ GDT_S_STATUS ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_CAM ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int PCI_DPMEM ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int bus_read_1 (struct resource*,scalar_t__) ; 
 int /*<<< orphan*/  bus_read_4 (struct resource*,scalar_t__) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/  bus_set_region_4 (struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,struct resource*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct gdt_softc*,void**) ; 
 int /*<<< orphan*/  bus_write_1 (struct resource*,scalar_t__,int) ; 
 int /*<<< orphan*/  bus_write_4 (struct resource*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  busdma_lock_mutex ; 
 struct gdt_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gdt_mpr_copy_cmd ; 
 int /*<<< orphan*/  gdt_mpr_get_status ; 
 int /*<<< orphan*/  gdt_mpr_intr ; 
 int /*<<< orphan*/  gdt_mpr_release_event ; 
 int /*<<< orphan*/  gdt_mpr_set_sema0 ; 
 int /*<<< orphan*/  gdt_mpr_test_busy ; 
 int /*<<< orphan*/  gdt_pci_enable_intr (struct gdt_softc*) ; 
 int /*<<< orphan*/  htole32 (int) ; 
 int /*<<< orphan*/  iir_attach (struct gdt_softc*) ; 
 int /*<<< orphan*/  iir_free (struct gdt_softc*) ; 
 scalar_t__ iir_init (struct gdt_softc*) ; 
 int /*<<< orphan*/  iir_intr ; 
 scalar_t__ le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_slot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_subdevice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_vendor (int /*<<< orphan*/ ) ; 
 int rman_get_start (struct resource*) ; 

__attribute__((used)) static int
iir_pci_attach(device_t dev)
{
    struct gdt_softc    *gdt;
    struct resource     *irq = NULL;
    int                 retries, rid, error = 0;
    void                *ih;
    u_int8_t            protocol;  

    gdt = device_get_softc(dev);
    mtx_init(&gdt->sc_lock, "iir", NULL, MTX_DEF);

    /* map DPMEM */
    rid = PCI_DPMEM;
    gdt->sc_dpmem = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid, RF_ACTIVE);
    if (gdt->sc_dpmem == NULL) {
        device_printf(dev, "can't allocate register resources\n");
        error = ENOMEM;
        goto err;
    }

    /* get IRQ */
    rid = 0;
    irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
                                 RF_ACTIVE | RF_SHAREABLE);
    if (irq == NULL) {
        device_printf(dev, "can't find IRQ value\n");
        error = ENOMEM;
        goto err;
    }

    gdt->sc_devnode = dev;
    gdt->sc_init_level = 0;
    gdt->sc_hanum = device_get_unit(dev);
    gdt->sc_bus = pci_get_bus(dev);
    gdt->sc_slot = pci_get_slot(dev);
    gdt->sc_vendor = pci_get_vendor(dev);
    gdt->sc_device = pci_get_device(dev);
    gdt->sc_subdevice = pci_get_subdevice(dev);
    gdt->sc_class = GDT_MPR;
/* no FC ctr.
    if (gdt->sc_device >= GDT_PCI_PRODUCT_FC)
        gdt->sc_class |= GDT_FC;
*/

    /* initialize RP controller */
    /* check and reset interface area */
    bus_write_4(gdt->sc_dpmem, GDT_MPR_IC, htole32(GDT_MPR_MAGIC));
    if (bus_read_4(gdt->sc_dpmem, GDT_MPR_IC) != htole32(GDT_MPR_MAGIC)) {
	device_printf(dev, "cannot access DPMEM at 0x%jx (shadowed?)\n",
	    rman_get_start(gdt->sc_dpmem));
        error = ENXIO;
        goto err;
    }
    bus_set_region_4(gdt->sc_dpmem, GDT_I960_SZ, htole32(0), GDT_MPR_SZ >> 2);

    /* Disable everything */
    bus_write_1(gdt->sc_dpmem, GDT_EDOOR_EN,
	bus_read_1(gdt->sc_dpmem, GDT_EDOOR_EN) | 4);
    bus_write_1(gdt->sc_dpmem, GDT_MPR_EDOOR, 0xff);
    bus_write_1(gdt->sc_dpmem, GDT_MPR_IC + GDT_S_STATUS, 0);
    bus_write_1(gdt->sc_dpmem, GDT_MPR_IC + GDT_CMD_INDEX, 0);

    bus_write_4(gdt->sc_dpmem, GDT_MPR_IC + GDT_S_INFO,
	htole32(rman_get_start(gdt->sc_dpmem)));
    bus_write_1(gdt->sc_dpmem, GDT_MPR_IC + GDT_S_CMD_INDX, 0xff);
    bus_write_1(gdt->sc_dpmem, GDT_MPR_LDOOR, 1);

    DELAY(20);
    retries = GDT_RETRIES;
    while (bus_read_1(gdt->sc_dpmem, GDT_MPR_IC + GDT_S_STATUS) != 0xff) {
        if (--retries == 0) {
            device_printf(dev, "DEINIT failed\n");
            error = ENXIO;
            goto err;
        }
        DELAY(1);
    }

    protocol = (uint8_t)le32toh(bus_read_4(gdt->sc_dpmem,
	    GDT_MPR_IC + GDT_S_INFO));
    bus_write_1(gdt->sc_dpmem, GDT_MPR_IC + GDT_S_STATUS, 0);
    if (protocol != GDT_PROTOCOL_VERSION) {
        device_printf(dev, "unsupported protocol %d\n", protocol);
        error = ENXIO;
        goto err;
    }
    
    /* special command to controller BIOS */
    bus_write_4(gdt->sc_dpmem, GDT_MPR_IC + GDT_S_INFO, htole32(0));
    bus_write_4(gdt->sc_dpmem, GDT_MPR_IC + GDT_S_INFO + sizeof (u_int32_t),
	htole32(0));
    bus_write_4(gdt->sc_dpmem, GDT_MPR_IC + GDT_S_INFO + 2 * sizeof (u_int32_t),
	htole32(1));
    bus_write_4(gdt->sc_dpmem, GDT_MPR_IC + GDT_S_INFO + 3 * sizeof (u_int32_t),
	htole32(0));
    bus_write_1(gdt->sc_dpmem, GDT_MPR_IC + GDT_S_CMD_INDX, 0xfe);
    bus_write_1(gdt->sc_dpmem, GDT_MPR_LDOOR, 1);

    DELAY(20);
    retries = GDT_RETRIES;
    while (bus_read_1(gdt->sc_dpmem, GDT_MPR_IC + GDT_S_STATUS) != 0xfe) {
        if (--retries == 0) {
            device_printf(dev, "initialization error\n");
            error = ENXIO;
            goto err;
        }
        DELAY(1);
    }

    bus_write_1(gdt->sc_dpmem, GDT_MPR_IC + GDT_S_STATUS, 0);

    gdt->sc_ic_all_size = GDT_MPR_SZ;
    
    gdt->sc_copy_cmd = gdt_mpr_copy_cmd;
    gdt->sc_get_status = gdt_mpr_get_status;
    gdt->sc_intr = gdt_mpr_intr;
    gdt->sc_release_event = gdt_mpr_release_event;
    gdt->sc_set_sema0 = gdt_mpr_set_sema0;
    gdt->sc_test_busy = gdt_mpr_test_busy;

    /* Allocate a dmatag representing the capabilities of this attachment */
    if (bus_dma_tag_create(/*parent*/bus_get_dma_tag(dev),
                           /*alignemnt*/1, /*boundary*/0,
                           /*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
                           /*highaddr*/BUS_SPACE_MAXADDR,
                           /*filter*/NULL, /*filterarg*/NULL,
                           /*maxsize*/BUS_SPACE_MAXSIZE_32BIT,
			   /*nsegments*/BUS_SPACE_UNRESTRICTED,
                           /*maxsegsz*/BUS_SPACE_MAXSIZE_32BIT,
			   /*flags*/0, /*lockfunc*/busdma_lock_mutex,
			   /*lockarg*/&gdt->sc_lock, &gdt->sc_parent_dmat) != 0) {
        error = ENXIO;
        goto err;
    }
    gdt->sc_init_level++;

    if (iir_init(gdt) != 0) {
        iir_free(gdt);
        error = ENXIO;
        goto err;
    }

    /* Register with the XPT */
    iir_attach(gdt);

    /* associate interrupt handler */
    if (bus_setup_intr(dev, irq, INTR_TYPE_CAM | INTR_MPSAFE, 
                        NULL, iir_intr, gdt, &ih )) {
        device_printf(dev, "Unable to register interrupt handler\n");
        error = ENXIO;
        goto err;
    }

    gdt_pci_enable_intr(gdt);
    return (0);
    
err:
    if (irq)
        bus_release_resource( dev, SYS_RES_IRQ, 0, irq );

    if (gdt->sc_dpmem)
        bus_release_resource( dev, SYS_RES_MEMORY, rid, gdt->sc_dpmem );
    mtx_destroy(&gdt->sc_lock);

    return (error);
}