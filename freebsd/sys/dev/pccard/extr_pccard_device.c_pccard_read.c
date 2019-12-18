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
struct uio {scalar_t__ uio_offset; int /*<<< orphan*/  uio_resid; } ;
struct pccard_softc {TYPE_1__* cis; } ;
struct cdev {struct pccard_softc* si_drv1; } ;
struct TYPE_2__ {scalar_t__ len; scalar_t__ buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,scalar_t__) ; 
 int uiomove (scalar_t__,int /*<<< orphan*/ ,struct uio*) ; 

__attribute__((used)) static	int
pccard_read(struct cdev *dev, struct uio *uio, int ioflag)
{
	struct pccard_softc *sc;

	sc = dev->si_drv1;
	/* EOF */
	if (sc->cis == NULL || uio->uio_offset > sc->cis->len)
		return (0);
	return (uiomove(sc->cis->buffer + uio->uio_offset,
	  MIN(uio->uio_resid, sc->cis->len - uio->uio_offset), uio));
}