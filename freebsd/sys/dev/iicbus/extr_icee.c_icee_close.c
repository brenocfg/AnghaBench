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
struct icee_softc {int /*<<< orphan*/  dev; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 struct icee_softc* CDEV2SOFTC (struct cdev*) ; 
 int /*<<< orphan*/  device_unbusy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
icee_close(struct cdev *dev, int fflag, int devtype, struct thread *td)
{
	struct icee_softc *sc;

	sc = CDEV2SOFTC(dev);
	device_unbusy(sc->dev);
	return (0);
}