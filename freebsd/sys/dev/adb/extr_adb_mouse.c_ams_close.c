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
struct cdev {int dummy; } ;
struct adb_mouse_softc {int /*<<< orphan*/  rsel; int /*<<< orphan*/  sc_cv; } ;

/* Variables and functions */
 struct adb_mouse_softc* CDEV_GET_SOFTC (struct cdev*) ; 
 int /*<<< orphan*/  PZERO ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selwakeuppri (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ams_close(struct cdev *dev, int flag, int fmt, struct thread *p)
{
	struct adb_mouse_softc *sc;

	sc = CDEV_GET_SOFTC(dev);

	cv_broadcast(&sc->sc_cv);
	selwakeuppri(&sc->rsel, PZERO);
	return (0);
}