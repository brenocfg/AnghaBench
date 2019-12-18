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
struct resource {int dummy; } ;
struct cbb_softc {int cardok; } ;
struct cbb_intrhand {int /*<<< orphan*/  cookie; struct cbb_softc* sc; void* arg; int /*<<< orphan*/ * intr; int /*<<< orphan*/ * filt; } ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  driver_filter_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_SETUP_INTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cbb_intrhand*,int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  cbb_enable_func_intr (struct cbb_softc*) ; 
 int /*<<< orphan*/ * cbb_func_filt ; 
 int /*<<< orphan*/ * cbb_func_intr ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct cbb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct cbb_intrhand*,int /*<<< orphan*/ ) ; 
 struct cbb_intrhand* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
cbb_setup_intr(device_t dev, device_t child, struct resource *irq,
  int flags, driver_filter_t *filt, driver_intr_t *intr, void *arg,
   void **cookiep)
{
	struct cbb_intrhand *ih;
	struct cbb_softc *sc = device_get_softc(dev);
	int err;

	if (filt == NULL && intr == NULL)
		return (EINVAL);
	ih = malloc(sizeof(struct cbb_intrhand), M_DEVBUF, M_NOWAIT);
	if (ih == NULL)
		return (ENOMEM);
	*cookiep = ih;
	ih->filt = filt;
	ih->intr = intr;
	ih->arg = arg;
	ih->sc = sc;
	/*
	 * XXX need to turn on ISA interrupts, if we ever support them, but
	 * XXX for now that's all we need to do.
	 */
	err = BUS_SETUP_INTR(device_get_parent(dev), child, irq, flags,
	    filt ? cbb_func_filt : NULL, intr ? cbb_func_intr : NULL, ih,
	    &ih->cookie);
	if (err != 0) {
		free(ih, M_DEVBUF);
		return (err);
	}
	cbb_enable_func_intr(sc);
	sc->cardok = 1;
	return 0;
}