#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct trapframe {int dummy; } ;
struct mips_pic_softc {int /*<<< orphan*/  pic_dev; } ;
typedef  int register_t ;
struct TYPE_6__ {int /*<<< orphan*/  td_intr_frame; } ;
struct TYPE_5__ {int td_pflags; struct trapframe* td_intr_frame; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MIPS_INT_MASK ; 
 TYPE_1__* PCPU_GET (TYPE_2__*) ; 
 int /*<<< orphan*/  PIC_INTR_ISRC (struct mips_pic_softc*,int) ; 
 int /*<<< orphan*/  PMC_FN_USER_CALLCHAIN ; 
 int TDP_CALLCHAIN ; 
 TYPE_2__* curthread ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int fls (int) ; 
 scalar_t__ intr_isrc_dispatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mips_rd_cause () ; 
 int mips_rd_status () ; 
 int /*<<< orphan*/  pic_irq_mask (struct mips_pic_softc*,int) ; 
 int /*<<< orphan*/  pmc_hook (TYPE_1__*,int /*<<< orphan*/ ,struct trapframe*) ; 

int
mips_pic_intr(void *arg)
{
	struct mips_pic_softc *sc = arg;
	register_t cause, status;
	int i, intr;

	cause = mips_rd_cause();
	status = mips_rd_status();
	intr = (cause & MIPS_INT_MASK) >> 8;
	/*
	 * Do not handle masked interrupts. They were masked by
	 * pre_ithread function (mips_mask_XXX_intr) and will be
	 * unmasked once ithread is through with handler
	 */
	intr &= (status & MIPS_INT_MASK) >> 8;
	while ((i = fls(intr)) != 0) {
		i--; /* Get a 0-offset interrupt. */
		intr &= ~(1 << i);

		if (intr_isrc_dispatch(PIC_INTR_ISRC(sc, i),
		    curthread->td_intr_frame) != 0) {
			device_printf(sc->pic_dev,
			    "Stray interrupt %u detected\n", i);
			pic_irq_mask(sc, i);
			continue;
		}
	}

	KASSERT(i == 0, ("all interrupts handled"));

#ifdef HWPMC_HOOKS
	if (pmc_hook && (PCPU_GET(curthread)->td_pflags & TDP_CALLCHAIN)) {
		struct trapframe *tf = PCPU_GET(curthread)->td_intr_frame;

		pmc_hook(PCPU_GET(curthread), PMC_FN_USER_CALLCHAIN, tf);
	}
#endif
	return (FILTER_HANDLED);
}