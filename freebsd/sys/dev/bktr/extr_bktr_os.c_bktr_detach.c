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
struct bktr_softc {int /*<<< orphan*/  res_mem; int /*<<< orphan*/  mem_rid; int /*<<< orphan*/  res_irq; int /*<<< orphan*/  irq_rid; int /*<<< orphan*/  res_ih; int /*<<< orphan*/  bktrdev; int /*<<< orphan*/  tunerdev; int /*<<< orphan*/  vbidev; int /*<<< orphan*/  vbimutex; int /*<<< orphan*/ * msp3400c_info; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_INTS_DISABLED ; 
 int /*<<< orphan*/  BKTR_GPIO_DMA_CTL ; 
 int /*<<< orphan*/  BKTR_INT_MASK ; 
 int /*<<< orphan*/  FIFO_RISC_DISABLED ; 
 int /*<<< orphan*/  OUTL (struct bktr_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTW (struct bktr_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bt848_i2c_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 struct bktr_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msp_detach (struct bktr_softc*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
bktr_detach( device_t dev )
{
	struct bktr_softc *bktr = device_get_softc(dev);

#ifdef BKTR_NEW_MSP34XX_DRIVER
	/* Disable the soundchip and kernel thread */
	if (bktr->msp3400c_info != NULL)
		msp_detach(bktr);
#endif

	/* Disable the brooktree device */
	OUTL(bktr, BKTR_INT_MASK, ALL_INTS_DISABLED);
	OUTW(bktr, BKTR_GPIO_DMA_CTL, FIFO_RISC_DISABLED);

#if defined(BKTR_USE_FREEBSD_SMBUS)
	if (bt848_i2c_detach(dev))
		printf("bktr%d: i2c_attach: can't attach\n",
		     device_get_unit(dev));
#endif
#ifdef USE_VBIMUTEX
        mtx_destroy(&bktr->vbimutex);
#endif

	/* Note: We do not free memory for RISC programs, grab buffer, vbi buffers */
	/* The memory is retained by the bktr_mem module so we can unload and */
	/* then reload the main bktr driver module */

	/* Unregister the /dev/bktrN, tunerN and vbiN devices,
	 * the aliases for unit 0 are automatically destroyed */
	destroy_dev(bktr->vbidev);
	destroy_dev(bktr->tunerdev);
	destroy_dev(bktr->bktrdev);

	/*
	 * Deallocate resources.
	 */
	bus_teardown_intr(dev, bktr->res_irq, bktr->res_ih);
	bus_release_resource(dev, SYS_RES_IRQ, bktr->irq_rid, bktr->res_irq);
	bus_release_resource(dev, SYS_RES_MEMORY, bktr->mem_rid, bktr->res_mem);
	 
	return 0;
}