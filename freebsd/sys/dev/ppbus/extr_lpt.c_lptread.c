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
struct uio {scalar_t__ uio_resid; } ;
struct lpt_data {int sc_flags; int /*<<< orphan*/  sc_statbuf; int /*<<< orphan*/  sc_dev; } ;
struct cdev {struct lpt_data* si_drv1; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUFSTATSIZE ; 
 int EPERM ; 
 int LP_BYPASS ; 
 int /*<<< orphan*/  PPB_NIBBLE ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,scalar_t__) ; 
 int ppb_1284_negociate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ppb_1284_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ppb_1284_terminate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_unlock (int /*<<< orphan*/ ) ; 
 int uiomove (int /*<<< orphan*/ ,int,struct uio*) ; 

__attribute__((used)) static int
lptread(struct cdev *dev, struct uio *uio, int ioflag)
{
	struct lpt_data *sc = dev->si_drv1;
	device_t lptdev = sc->sc_dev;
	device_t ppbus = device_get_parent(lptdev);
	int error = 0, len;

	if (sc->sc_flags & LP_BYPASS) {
		/* we can't do reads in bypass mode */
		return (EPERM);
	}

	ppb_lock(ppbus);
	if ((error = ppb_1284_negociate(ppbus, PPB_NIBBLE, 0))) {
		ppb_unlock(ppbus);
		return (error);
	}

	/* read data in an other buffer, read/write may be simultaneous */
	len = 0;
	while (uio->uio_resid) {
		if ((error = ppb_1284_read(ppbus, PPB_NIBBLE,
				sc->sc_statbuf, min(BUFSTATSIZE,
				uio->uio_resid), &len))) {
			goto error;
		}

		if (!len)
			goto error;		/* no more data */

		ppb_unlock(ppbus);
		error = uiomove(sc->sc_statbuf, len, uio);
		ppb_lock(ppbus);
		if (error)
			goto error;
	}

error:
	ppb_1284_terminate(ppbus);
	ppb_unlock(ppbus);
	return (error);
}