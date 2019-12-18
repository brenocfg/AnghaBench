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
struct pccard_function {int (* intr_filter ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  intr_handler_arg; int /*<<< orphan*/  sc; } ;

/* Variables and functions */
 int FILTER_SCHEDULE_THREAD ; 
 int FILTER_STRAY ; 
 int /*<<< orphan*/  PCCARD_CCR_STATUS ; 
 int PCCARD_CCR_STATUS_INTR ; 
 int pccard_ccr_read (struct pccard_function*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pccard_ccr_write (struct pccard_function*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pccard_mfc (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pccard_filter(void *arg)
{
	struct pccard_function *pf = (struct pccard_function*) arg;
	int reg;
	int doisr = 1;

	/*
	 * MFC cards know if they interrupted, so we have to ack the
	 * interrupt and call the ISR.  Non-MFC cards don't have these
	 * bits, so they always get called.  Many non-MFC cards have
	 * this bit set always upon read, but some do not.
	 *
	 * We always ack the interrupt, even if there's no ISR
	 * for the card.  This is done on the theory that acking
	 * the interrupt will pacify the card enough to keep an
	 * interrupt storm from happening.  Of course this won't
	 * help in the non-MFC case.
	 *
	 * This has no impact for MPSAFEness of the client drivers.
	 * We register this with whatever flags the intr_handler
	 * was registered with.  All these functions are MPSAFE.
	 */
	if (pccard_mfc(pf->sc)) {
		reg = pccard_ccr_read(pf, PCCARD_CCR_STATUS);
		if (reg & PCCARD_CCR_STATUS_INTR)
			pccard_ccr_write(pf, PCCARD_CCR_STATUS,
			    reg & ~PCCARD_CCR_STATUS_INTR);
		else
			doisr = 0;
	}
	if (doisr) {
		if (pf->intr_filter != NULL)
			return (pf->intr_filter(pf->intr_handler_arg));
		return (FILTER_SCHEDULE_THREAD);
	}
	return (FILTER_STRAY);
}