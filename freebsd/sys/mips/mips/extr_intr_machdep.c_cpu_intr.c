#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct trapframe {int dummy; } ;
struct intr_event {int /*<<< orphan*/  ie_handlers; } ;
typedef  int register_t ;
struct TYPE_3__ {int td_pflags; } ;

/* Variables and functions */
 scalar_t__ CK_SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MIPS_INT_MASK ; 
 int /*<<< orphan*/  NSOFT_IRQS ; 
 TYPE_1__* PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMC_FN_USER_CALLCHAIN ; 
 int TDP_CALLCHAIN ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  curthread ; 
 int fls (int) ; 
 struct intr_event** hardintr_events ; 
 scalar_t__ intr_event_handle (struct intr_event*,struct trapframe*) ; 
 int /*<<< orphan*/ * mips_intr_counters ; 
 int /*<<< orphan*/  mips_intrcnt_inc (int /*<<< orphan*/ ) ; 
 int mips_rd_cause () ; 
 int mips_rd_status () ; 
 int /*<<< orphan*/  pmc_hook (TYPE_1__*,int /*<<< orphan*/ ,struct trapframe*) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 struct intr_event** softintr_events ; 

void
cpu_intr(struct trapframe *tf)
{
	struct intr_event *event;
	register_t cause, status;
	int hard, i, intr;

	critical_enter();

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
		intr &= ~(1 << (i - 1));
		switch (i) {
		case 1: case 2:
			/* Software interrupt. */
			i--; /* Get a 0-offset interrupt. */
			hard = 0;
			event = softintr_events[i];
			mips_intrcnt_inc(mips_intr_counters[i]);
			break;
		default:
			/* Hardware interrupt. */
			i -= 2; /* Trim software interrupt bits. */
			i--; /* Get a 0-offset interrupt. */
			hard = 1;
			event = hardintr_events[i];
			mips_intrcnt_inc(mips_intr_counters[NSOFT_IRQS + i]);
			break;
		}

		if (!event || CK_SLIST_EMPTY(&event->ie_handlers)) {
			printf("stray %s interrupt %d\n",
			    hard ? "hard" : "soft", i);
			continue;
		}

		if (intr_event_handle(event, tf) != 0) {
			printf("stray %s interrupt %d\n", 
			    hard ? "hard" : "soft", i);
		}
	}

	KASSERT(i == 0, ("all interrupts handled"));

	critical_exit();

#ifdef HWPMC_HOOKS
	if (pmc_hook && (PCPU_GET(curthread)->td_pflags & TDP_CALLCHAIN))
		pmc_hook(PCPU_GET(curthread), PMC_FN_USER_CALLCHAIN, tf);
#endif
}