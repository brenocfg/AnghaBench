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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {char* rm_descr; void* rm_type; } ;
struct gt_pci_softc {int sc_mem; int sc_imask; int sc_elcr; unsigned int sc_reserved; int /*<<< orphan*/  sc_ih; int /*<<< orphan*/ * sc_irq; void* sc_ioh_elcr; int /*<<< orphan*/  sc_st; void* sc_ioh_icu2; void* sc_ioh_icu1; scalar_t__ sc_io; TYPE_1__ sc_irq_rman; TYPE_1__ sc_mem_rman; TYPE_1__ sc_io_rman; scalar_t__ sc_busno; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int ICW1_IC4 ; 
 int ICW1_RESET ; 
 int ICW4_8086 ; 
 int /*<<< orphan*/  INTR_TYPE_MISC ; 
 int IO_ICU1 ; 
 int IO_ICU2 ; 
 scalar_t__ MALTA_PCI0_IO_BASE ; 
 int MALTA_PCIMEM1_BASE ; 
 int MALTA_PCIMEM1_SIZE ; 
 int /*<<< orphan*/  MALTA_SOUTHBRIDGE_INTR ; 
 void* MIPS_PHYS_TO_KSEG1 (scalar_t__) ; 
 int OCW3_ESMM ; 
 int OCW3_RR ; 
 int OCW3_SEL ; 
 int OCW3_SMM ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 void* RMAN_ARRAY ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct gt_pci_softc*,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_space_map (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  bus_space_write_1 (int /*<<< orphan*/ ,void*,int,int) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct gt_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gt_pci_intr ; 
 int /*<<< orphan*/  mips_bus_space_generic ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ rman_init (TYPE_1__*) ; 
 scalar_t__ rman_manage_region (TYPE_1__*,int,int) ; 

__attribute__((used)) static int
gt_pci_attach(device_t dev)
{

	uint32_t busno;				       
	struct gt_pci_softc *sc = device_get_softc(dev);
	int rid;

	busno = 0;
	sc->sc_dev = dev;
	sc->sc_busno = busno;
	sc->sc_st = mips_bus_space_generic;

	/* Use KSEG1 to access IO ports for it is uncached */
	sc->sc_io = MALTA_PCI0_IO_BASE;
	sc->sc_io_rman.rm_type = RMAN_ARRAY;
	sc->sc_io_rman.rm_descr = "GT64120 PCI I/O Ports";
	/* 
	 * First 256 bytes are ISA's registers: e.g. i8259's
	 * So do not use them for general purpose PCI I/O window
	 */
	if (rman_init(&sc->sc_io_rman) != 0 ||
	    rman_manage_region(&sc->sc_io_rman, 0x100, 0xffff) != 0) {
		panic("gt_pci_attach: failed to set up I/O rman");
	}

	/* Use KSEG1 to access PCI memory for it is uncached */
	sc->sc_mem = MALTA_PCIMEM1_BASE;
	sc->sc_mem_rman.rm_type = RMAN_ARRAY;
	sc->sc_mem_rman.rm_descr = "GT64120 PCI Memory";
	if (rman_init(&sc->sc_mem_rman) != 0 ||
	    rman_manage_region(&sc->sc_mem_rman, 
	    sc->sc_mem, sc->sc_mem + MALTA_PCIMEM1_SIZE) != 0) {
		panic("gt_pci_attach: failed to set up memory rman");
	}
	sc->sc_irq_rman.rm_type = RMAN_ARRAY;
	sc->sc_irq_rman.rm_descr = "GT64120 PCI IRQs";
	if (rman_init(&sc->sc_irq_rman) != 0 ||
	    rman_manage_region(&sc->sc_irq_rman, 1, 31) != 0)
		panic("gt_pci_attach: failed to set up IRQ rman");

	/*
	 * Map the PIC/ELCR registers.
	 */
#if 0
	if (bus_space_map(sc->sc_st, 0x4d0, 2, 0, &sc->sc_ioh_elcr) != 0)
		device_printf(dev, "unable to map ELCR registers\n");
	if (bus_space_map(sc->sc_st, IO_ICU1, 2, 0, &sc->sc_ioh_icu1) != 0)
		device_printf(dev, "unable to map ICU1 registers\n");
	if (bus_space_map(sc->sc_st, IO_ICU2, 2, 0, &sc->sc_ioh_icu2) != 0)
		device_printf(dev, "unable to map ICU2 registers\n");
#else
	sc->sc_ioh_elcr = MIPS_PHYS_TO_KSEG1(sc->sc_io + 0x4d0);
	sc->sc_ioh_icu1 = MIPS_PHYS_TO_KSEG1(sc->sc_io + IO_ICU1);
	sc->sc_ioh_icu2 = MIPS_PHYS_TO_KSEG1(sc->sc_io + IO_ICU2);
#endif	


	/* All interrupts default to "masked off". */
	sc->sc_imask = 0xffff;

	/* All interrupts default to edge-triggered. */
	sc->sc_elcr = 0;

	/*
	 * Initialize the 8259s.
	 */
	/* reset, program device, 4 bytes */
	bus_space_write_1(sc->sc_st, sc->sc_ioh_icu1, 0,
	    ICW1_RESET | ICW1_IC4);
	/*
	 * XXX: values from NetBSD's <dev/ic/i8259reg.h>
	 */	 
	bus_space_write_1(sc->sc_st, sc->sc_ioh_icu1, 1,
	    0/*XXX*/);
	bus_space_write_1(sc->sc_st, sc->sc_ioh_icu1, 1,
	    1 << 2);
	bus_space_write_1(sc->sc_st, sc->sc_ioh_icu1, 1,
	    ICW4_8086);

	/* mask all interrupts */
	bus_space_write_1(sc->sc_st, sc->sc_ioh_icu1, 1,
	    sc->sc_imask & 0xff);

	/* enable special mask mode */
	bus_space_write_1(sc->sc_st, sc->sc_ioh_icu1, 0,
	    OCW3_SEL | OCW3_ESMM | OCW3_SMM);

	/* read IRR by default */
	bus_space_write_1(sc->sc_st, sc->sc_ioh_icu1, 0,
	    OCW3_SEL | OCW3_RR);

	/* reset, program device, 4 bytes */
	bus_space_write_1(sc->sc_st, sc->sc_ioh_icu2, 0,
	    ICW1_RESET | ICW1_IC4);
	bus_space_write_1(sc->sc_st, sc->sc_ioh_icu2, 1,
	    0/*XXX*/);
	bus_space_write_1(sc->sc_st, sc->sc_ioh_icu2, 1,
	    1 << 2);
	bus_space_write_1(sc->sc_st, sc->sc_ioh_icu2, 1,
	    ICW4_8086);

	/* mask all interrupts */
	bus_space_write_1(sc->sc_st, sc->sc_ioh_icu2, 1,
	    sc->sc_imask & 0xff);

	/* enable special mask mode */
	bus_space_write_1(sc->sc_st, sc->sc_ioh_icu2, 0,
	    OCW3_SEL | OCW3_ESMM | OCW3_SMM);

	/* read IRR by default */
	bus_space_write_1(sc->sc_st, sc->sc_ioh_icu2, 0,
	    OCW3_SEL | OCW3_RR);

	/*
	 * Default all interrupts to edge-triggered.
	 */
	bus_space_write_1(sc->sc_st, sc->sc_ioh_elcr, 0,
	    sc->sc_elcr & 0xff);
	bus_space_write_1(sc->sc_st, sc->sc_ioh_elcr, 1,
	    (sc->sc_elcr >> 8) & 0xff);

	/*
	 * Some ISA interrupts are reserved for devices that
	 * we know are hard-wired to certain IRQs.
	 */
	sc->sc_reserved =
		(1U << 0) |     /* timer */
		(1U << 1) |     /* keyboard controller (keyboard) */
		(1U << 2) |     /* PIC cascade */
		(1U << 3) |     /* COM 2 */
		(1U << 4) |     /* COM 1 */
		(1U << 6) |     /* floppy */
		(1U << 7) |     /* centronics */
		(1U << 8) |     /* RTC */
		(1U << 9) |	/* I2C */
		(1U << 12) |    /* keyboard controller (mouse) */
		(1U << 14) |    /* IDE primary */
		(1U << 15);     /* IDE secondary */

	/* Hook up our interrupt handler. */
	if ((sc->sc_irq = bus_alloc_resource(dev, SYS_RES_IRQ, &rid, 
	    MALTA_SOUTHBRIDGE_INTR, MALTA_SOUTHBRIDGE_INTR, 1, 
	    RF_SHAREABLE | RF_ACTIVE)) == NULL) {
		device_printf(dev, "unable to allocate IRQ resource\n");
		return ENXIO;
	}

	if ((bus_setup_intr(dev, sc->sc_irq, INTR_TYPE_MISC,
			    gt_pci_intr, NULL, sc, &sc->sc_ih))) {
		device_printf(dev, 
		    "WARNING: unable to register interrupt handler\n");
		return ENXIO;
	}

	/* Initialize memory and i/o rmans. */
	device_add_child(dev, "pci", -1);
	return (bus_generic_attach(dev));
}