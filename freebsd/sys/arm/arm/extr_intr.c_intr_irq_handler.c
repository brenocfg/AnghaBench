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
struct intr_event {int dummy; } ;
struct TYPE_3__ {int td_pflags; } ;

/* Variables and functions */
 TYPE_1__* PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMC_FN_USER_CALLCHAIN ; 
 int TDP_CALLCHAIN ; 
 int /*<<< orphan*/  VM_CNT_INC (int /*<<< orphan*/ ) ; 
 int arm_get_next_irq (int) ; 
 int /*<<< orphan*/  arm_mask_irq (int) ; 
 int /*<<< orphan*/  curthread ; 
 scalar_t__ intr_event_handle (struct intr_event*,struct trapframe*) ; 
 struct intr_event** intr_events ; 
 int /*<<< orphan*/ * intrcnt ; 
 int /*<<< orphan*/  pmc_hook (TYPE_1__*,int /*<<< orphan*/ ,struct trapframe*) ; 
 int /*<<< orphan*/  v_intr ; 

void
intr_irq_handler(struct trapframe *frame)
{
	struct intr_event *event;
	int i;

	VM_CNT_INC(v_intr);
	i = -1;
	while ((i = arm_get_next_irq(i)) != -1) {
		intrcnt[i]++;
		event = intr_events[i];
		if (intr_event_handle(event, frame) != 0) {
			/* XXX: Log stray IRQs */
			arm_mask_irq(i);
		}
	}
#ifdef HWPMC_HOOKS
	if (pmc_hook && (PCPU_GET(curthread)->td_pflags & TDP_CALLCHAIN))
		pmc_hook(PCPU_GET(curthread), PMC_FN_USER_CALLCHAIN, frame);
#endif
}