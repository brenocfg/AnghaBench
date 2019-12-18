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
struct ti_softc {int /*<<< orphan*/  ti_flags; } ;
struct thread {int dummy; } ;
struct cdev {struct ti_softc* si_drv1; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  TI_FLAG_DEBUGING ; 
 int /*<<< orphan*/  TI_LOCK (struct ti_softc*) ; 
 int /*<<< orphan*/  TI_UNLOCK (struct ti_softc*) ; 

__attribute__((used)) static int
ti_close(struct cdev *dev, int flag, int fmt, struct thread *td)
{
	struct ti_softc *sc;

	sc = dev->si_drv1;
	if (sc == NULL)
		return (ENODEV);

	TI_LOCK(sc);
	sc->ti_flags &= ~TI_FLAG_DEBUGING;
	TI_UNLOCK(sc);

	return (0);
}