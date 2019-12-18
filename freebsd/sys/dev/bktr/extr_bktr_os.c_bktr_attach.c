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
typedef  int u_long ;
struct bktr_softc {int /*<<< orphan*/ * res_mem; scalar_t__ mem_rid; int /*<<< orphan*/ * res_irq; scalar_t__ irq_rid; void* vbidev; void* vbidev_alias; void* tunerdev; void* tunerdev_alias; void* bktrdev; void* bktrdev_alias; int /*<<< orphan*/  res_ih; int /*<<< orphan*/  memh; int /*<<< orphan*/  memt; int /*<<< orphan*/  bktr_xname; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_INTS_DISABLED ; 
 int /*<<< orphan*/  BKTR_GPIO_DMA_CTL ; 
 int /*<<< orphan*/  BKTR_INT_MASK ; 
 int BROOKTREE_DEF_LATENCY_VALUE ; 
 int /*<<< orphan*/  BROOKTREE_IRQ ; 
 int ENXIO ; 
 int /*<<< orphan*/  FIFO_RISC_DISABLED ; 
 int /*<<< orphan*/  INTR_TYPE_TTY ; 
 int /*<<< orphan*/  OUTL (struct bktr_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTW (struct bktr_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_INTERRUPT_REG ; 
 int PCI_LATENCY_TIMER ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bktr_cdevsw ; 
 int /*<<< orphan*/  bktr_intr ; 
 scalar_t__ bootverbose ; 
 scalar_t__ bt848_i2c_attach (int /*<<< orphan*/ ) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bktr_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  common_bktr_attach (struct bktr_softc*,unsigned int,int,unsigned int) ; 
 struct bktr_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 unsigned int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 void* make_dev (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,unsigned int) ; 
 void* make_dev_alias (void*,char*) ; 
 int pci_conf_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_conf_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 
 unsigned int pci_get_revid (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,unsigned int) ; 
 int /*<<< orphan*/  tag ; 

__attribute__((used)) static int
bktr_attach( device_t dev )
{
	u_long		latency;
	u_long		fun;
	unsigned int	rev;
	unsigned int	unit;
	int		error = 0;
#ifdef BROOKTREE_IRQ
	u_long		old_irq, new_irq;
#endif 

        struct bktr_softc *bktr = device_get_softc(dev);

	unit = device_get_unit(dev);

	/* build the device name for bktr_name() */
	snprintf(bktr->bktr_xname, sizeof(bktr->bktr_xname), "bktr%d",unit);

	/*
	 * Enable bus mastering and Memory Mapped device
	 */
	pci_enable_busmaster(dev);

	/*
	 * Map control/status registers.
	 */
	bktr->mem_rid = PCIR_BAR(0);
	bktr->res_mem = bus_alloc_resource_any(dev, SYS_RES_MEMORY, 
					&bktr->mem_rid, RF_ACTIVE);

	if (!bktr->res_mem) {
		device_printf(dev, "could not map memory\n");
		error = ENXIO;
		goto fail;
	}
	bktr->memt = rman_get_bustag(bktr->res_mem);
	bktr->memh = rman_get_bushandle(bktr->res_mem);


	/*
	 * Disable the brooktree device
	 */
	OUTL(bktr, BKTR_INT_MASK, ALL_INTS_DISABLED);
	OUTW(bktr, BKTR_GPIO_DMA_CTL, FIFO_RISC_DISABLED);


#ifdef BROOKTREE_IRQ		/* from the configuration file */
	old_irq = pci_conf_read(tag, PCI_INTERRUPT_REG);
	pci_conf_write(tag, PCI_INTERRUPT_REG, BROOKTREE_IRQ);
	new_irq = pci_conf_read(tag, PCI_INTERRUPT_REG);
	printf("bktr%d: attach: irq changed from %d to %d\n",
		unit, (old_irq & 0xff), (new_irq & 0xff));
#endif 

	/*
	 * Allocate our interrupt.
	 */
	bktr->irq_rid = 0;
	bktr->res_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, 
				&bktr->irq_rid, RF_SHAREABLE | RF_ACTIVE);
	if (bktr->res_irq == NULL) {
		device_printf(dev, "could not map interrupt\n");
		error = ENXIO;
		goto fail;
	}

	error = bus_setup_intr(dev, bktr->res_irq, INTR_TYPE_TTY,
                               NULL, bktr_intr, bktr, &bktr->res_ih);
	if (error) {
		device_printf(dev, "could not setup irq\n");
		goto fail;

	}


	/* Update the Device Control Register */
	/* on Bt878 and Bt879 cards           */
	fun = pci_read_config( dev, 0x40, 2);
        fun = fun | 1;	/* Enable writes to the sub-system vendor ID */

#if defined( BKTR_430_FX_MODE )
	if (bootverbose) printf("Using 430 FX chipset compatibility mode\n");
        fun = fun | 2;	/* Enable Intel 430 FX compatibility mode */
#endif

#if defined( BKTR_SIS_VIA_MODE )
	if (bootverbose) printf("Using SiS/VIA chipset compatibility mode\n");
        fun = fun | 4;	/* Enable SiS/VIA compatibility mode (useful for
                           OPTi chipset motherboards too */
#endif
	pci_write_config(dev, 0x40, fun, 2);

#if defined(BKTR_USE_FREEBSD_SMBUS)
	if (bt848_i2c_attach(dev))
		printf("bktr%d: i2c_attach: can't attach\n", unit);
#endif

/*
 * PCI latency timer.  32 is a good value for 4 bus mastering slots, if
 * you have more than four, then 16 would probably be a better value.
 */
#ifndef BROOKTREE_DEF_LATENCY_VALUE
#define BROOKTREE_DEF_LATENCY_VALUE	10
#endif
	latency = pci_read_config(dev, PCI_LATENCY_TIMER, 4);
	latency = (latency >> 8) & 0xff;
	if ( bootverbose ) {
		if (latency)
			printf("brooktree%d: PCI bus latency is", unit);
		else
			printf("brooktree%d: PCI bus latency was 0 changing to",
				unit);
	}
	if ( !latency ) {
		latency = BROOKTREE_DEF_LATENCY_VALUE;
		pci_write_config(dev, PCI_LATENCY_TIMER, latency<<8, 4);
	}
	if ( bootverbose ) {
		printf(" %d.\n", (int) latency);
	}

	/* read the pci device id and revision id */
	fun = pci_get_devid(dev);
        rev = pci_get_revid(dev);

	/* call the common attach code */
	common_bktr_attach( bktr, unit, fun, rev );

	/* make the device entries */
	bktr->bktrdev = make_dev(&bktr_cdevsw, unit,    
				0, 0, 0444, "bktr%d",  unit);
	bktr->tunerdev= make_dev(&bktr_cdevsw, unit+16,
				0, 0, 0444, "tuner%d", unit);
	bktr->vbidev  = make_dev(&bktr_cdevsw, unit+32,
				0, 0, 0444, "vbi%d"  , unit);


	/* if this is unit 0 (/dev/bktr0, /dev/tuner0, /dev/vbi0) then make */
	/* alias entries to /dev/bktr /dev/tuner and /dev/vbi */
#if (__FreeBSD_version >=500000)
	if (unit == 0) {
		bktr->bktrdev_alias = make_dev_alias(bktr->bktrdev,  "bktr");
		bktr->tunerdev_alias= make_dev_alias(bktr->tunerdev, "tuner");
		bktr->vbidev_alias  = make_dev_alias(bktr->vbidev,   "vbi");
	}
#endif

	return 0;

fail:
	if (bktr->res_irq)
		bus_release_resource(dev, SYS_RES_IRQ, bktr->irq_rid, bktr->res_irq);
	if (bktr->res_mem)
		bus_release_resource(dev, SYS_RES_MEMORY, bktr->mem_rid, bktr->res_mem);
	return error;

}