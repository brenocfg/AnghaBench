#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vmem_addr_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  void* u_int ;
struct TYPE_2__ {int /*<<< orphan*/  lpi_base; void* lpi_free; void* lpi_num; scalar_t__ lpi_busy; } ;
struct its_dev {scalar_t__ itt; TYPE_1__ lpis; int /*<<< orphan*/  itt_size; int /*<<< orphan*/  devid; int /*<<< orphan*/  pci_dev; } ;
struct gicv3_its_softc {int /*<<< orphan*/  sc_its_dev_lock; int /*<<< orphan*/  sc_its_dev_list; int /*<<< orphan*/  sc_irq_alloc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GITS_TYPER ; 
 size_t GITS_TYPER_ITTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPI_INT_TRANS_TAB_ALIGN ; 
 int /*<<< orphan*/  LPI_INT_TRANS_TAB_MAX_ADDR ; 
 size_t MAX (void*,int) ; 
 int M_FIRSTFIT ; 
 int /*<<< orphan*/  M_GICV3_ITS ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct its_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ contigmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gicv3_its_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  free (struct its_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gic_its_read_8 (struct gicv3_its_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_cmd_mapd (int /*<<< orphan*/ ,struct its_dev*,int) ; 
 struct its_dev* its_device_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_get_devid (int /*<<< orphan*/ ) ; 
 struct its_dev* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  roundup2 (size_t,int) ; 
 scalar_t__ vmem_alloc (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static struct its_dev *
its_device_get(device_t dev, device_t child, u_int nvecs)
{
	struct gicv3_its_softc *sc;
	struct its_dev *its_dev;
	vmem_addr_t irq_base;
	size_t esize;

	sc = device_get_softc(dev);

	its_dev = its_device_find(dev, child);
	if (its_dev != NULL)
		return (its_dev);

	its_dev = malloc(sizeof(*its_dev), M_GICV3_ITS, M_NOWAIT | M_ZERO);
	if (its_dev == NULL)
		return (NULL);

	its_dev->pci_dev = child;
	its_dev->devid = its_get_devid(child);

	its_dev->lpis.lpi_busy = 0;
	its_dev->lpis.lpi_num = nvecs;
	its_dev->lpis.lpi_free = nvecs;

	if (vmem_alloc(sc->sc_irq_alloc, nvecs, M_FIRSTFIT | M_NOWAIT,
	    &irq_base) != 0) {
		free(its_dev, M_GICV3_ITS);
		return (NULL);
	}
	its_dev->lpis.lpi_base = irq_base;

	/* Get ITT entry size */
	esize = GITS_TYPER_ITTES(gic_its_read_8(sc, GITS_TYPER));

	/*
	 * Allocate ITT for this device.
	 * PA has to be 256 B aligned. At least two entries for device.
	 */
	its_dev->itt_size = roundup2(MAX(nvecs, 2) * esize, 256);
	its_dev->itt = (vm_offset_t)contigmalloc(its_dev->itt_size,
	    M_GICV3_ITS, M_NOWAIT | M_ZERO, 0, LPI_INT_TRANS_TAB_MAX_ADDR,
	    LPI_INT_TRANS_TAB_ALIGN, 0);
	if (its_dev->itt == 0) {
		vmem_free(sc->sc_irq_alloc, its_dev->lpis.lpi_base, nvecs);
		free(its_dev, M_GICV3_ITS);
		return (NULL);
	}

	mtx_lock_spin(&sc->sc_its_dev_lock);
	TAILQ_INSERT_TAIL(&sc->sc_its_dev_list, its_dev, entry);
	mtx_unlock_spin(&sc->sc_its_dev_lock);

	/* Map device to its ITT */
	its_cmd_mapd(dev, its_dev, 1);

	return (its_dev);
}