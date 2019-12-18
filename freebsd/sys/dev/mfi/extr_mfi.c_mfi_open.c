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
struct thread {int dummy; } ;
struct mfi_softc {int /*<<< orphan*/  mfi_io_lock; int /*<<< orphan*/  mfi_flags; scalar_t__ mfi_detaching; } ;
struct cdev {struct mfi_softc* si_drv1; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MFI_FLAGS_OPEN ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mfi_open(struct cdev *dev, int flags, int fmt, struct thread *td)
{
	struct mfi_softc *sc;
	int error;

	sc = dev->si_drv1;

	mtx_lock(&sc->mfi_io_lock);
	if (sc->mfi_detaching)
		error = ENXIO;
	else {
		sc->mfi_flags |= MFI_FLAGS_OPEN;
		error = 0;
	}
	mtx_unlock(&sc->mfi_io_lock);

	return (error);
}