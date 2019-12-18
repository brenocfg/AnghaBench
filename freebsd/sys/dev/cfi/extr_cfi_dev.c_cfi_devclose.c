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
struct thread {int /*<<< orphan*/ * td_proc; } ;
struct cfi_softc {int /*<<< orphan*/ * sc_opened; scalar_t__ sc_writing; } ;
struct cdev {struct cfi_softc* si_drv1; } ;

/* Variables and functions */
 int ENXIO ; 
 int cfi_block_finish (struct cfi_softc*) ; 

__attribute__((used)) static int
cfi_devclose(struct cdev *dev, int fflag, int devtype, struct thread *td)
{
	struct cfi_softc *sc;
	int error;

	sc = dev->si_drv1;
	/* Sanity. Not really necessary. */
	if (sc->sc_opened != td->td_proc)
		return (ENXIO);

	error = (sc->sc_writing) ? cfi_block_finish(sc) : 0;
	sc->sc_opened = NULL;
	return (error);
}