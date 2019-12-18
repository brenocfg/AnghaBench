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
struct pccard_softc {scalar_t__ cis_open; int /*<<< orphan*/ * cis; } ;
struct cdev {struct pccard_softc* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static	int
pccard_close(struct cdev *dev, int fflags, int devtype, struct thread *td)
{
	struct pccard_softc *sc;

	sc = dev->si_drv1;
	free(sc->cis, M_TEMP);
	sc->cis = NULL;
	sc->cis_open = 0;
	return (0);
}