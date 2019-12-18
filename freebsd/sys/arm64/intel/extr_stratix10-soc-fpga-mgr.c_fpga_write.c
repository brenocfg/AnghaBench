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
typedef  scalar_t__ vm_offset_t ;
struct uio {scalar_t__ uio_resid; } ;
struct TYPE_2__ {scalar_t__ vaddr; scalar_t__ fill; } ;
struct fpgamgr_s10_softc {scalar_t__ opened; int /*<<< orphan*/  sx; TYPE_1__ mem; } ;
struct cdev {struct fpgamgr_s10_softc* si_drv1; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int MIN (scalar_t__,scalar_t__) ; 
 scalar_t__ SVC_BUF_SIZE ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiomove (void*,int,struct uio*) ; 

__attribute__((used)) static int
fpga_write(struct cdev *dev, struct uio *uio, int ioflag)
{
	struct fpgamgr_s10_softc *sc;
	vm_offset_t addr;
	int amnt;

	sc = dev->si_drv1;

	sx_xlock(&sc->sx);
	if (sc->opened == 0) {
		/* Device closed. */
		sx_xunlock(&sc->sx);
		return (ENXIO);
	}

	while (uio->uio_resid > 0) {
		addr = sc->mem.vaddr + sc->mem.fill;
		if (sc->mem.fill >= SVC_BUF_SIZE)
			return (ENOMEM);
		amnt = MIN(uio->uio_resid, (SVC_BUF_SIZE - sc->mem.fill));
		uiomove((void *)addr, amnt, uio);
		sc->mem.fill += amnt;
	}

	sx_xunlock(&sc->sx);

	return (0);
}