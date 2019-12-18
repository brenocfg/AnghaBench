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
struct cmx_softc {int open; int /*<<< orphan*/  dev; scalar_t__ dying; } ;
struct cdev {struct cmx_softc* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMX_LOCK (struct cmx_softc*) ; 
 int /*<<< orphan*/  CMX_UNLOCK (struct cmx_softc*) ; 
 int /*<<< orphan*/  DEBUG_printf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,struct thread*) ; 
 int EBUSY ; 
 int ENXIO ; 
 int /*<<< orphan*/  MODEBITS ; 

__attribute__((used)) static int
cmx_open(struct cdev *cdev, int flags, int fmt, struct thread *td)
{
	struct cmx_softc *sc = cdev->si_drv1;

	if (sc == NULL || sc->dying)
		return ENXIO;

	CMX_LOCK(sc);
	if (sc->open) {
		CMX_UNLOCK(sc);
		return EBUSY;
	}
	sc->open = 1;
	CMX_UNLOCK(sc);

	DEBUG_printf(sc->dev, "open (flags=%b thread=%p)\n",
			flags, MODEBITS, td);
	return 0;
}