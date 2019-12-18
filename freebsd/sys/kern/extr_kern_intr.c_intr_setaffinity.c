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
struct intr_event {int dummy; } ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 scalar_t__ CPU_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ISSET (int,int /*<<< orphan*/ *) ; 
 int CPU_SETSIZE ; 
#define  CPU_WHICH_INTRHANDLER 130 
#define  CPU_WHICH_IRQ 129 
#define  CPU_WHICH_ITHREAD 128 
 int EINVAL ; 
 int ESRCH ; 
 int NOCPU ; 
 int /*<<< orphan*/  cpuset_root ; 
 int intr_event_bind (struct intr_event*,int) ; 
 int intr_event_bind_irqonly (struct intr_event*,int) ; 
 int intr_event_bind_ithread (struct intr_event*,int) ; 
 struct intr_event* intr_lookup (int) ; 

int
intr_setaffinity(int irq, int mode, void *m)
{
	struct intr_event *ie;
	cpuset_t *mask;
	int cpu, n;

	mask = m;
	cpu = NOCPU;
	/*
	 * If we're setting all cpus we can unbind.  Otherwise make sure
	 * only one cpu is in the set.
	 */
	if (CPU_CMP(cpuset_root, mask)) {
		for (n = 0; n < CPU_SETSIZE; n++) {
			if (!CPU_ISSET(n, mask))
				continue;
			if (cpu != NOCPU)
				return (EINVAL);
			cpu = n;
		}
	}
	ie = intr_lookup(irq);
	if (ie == NULL)
		return (ESRCH);
	switch (mode) {
	case CPU_WHICH_IRQ:
		return (intr_event_bind(ie, cpu));
	case CPU_WHICH_INTRHANDLER:
		return (intr_event_bind_irqonly(ie, cpu));
	case CPU_WHICH_ITHREAD:
		return (intr_event_bind_ithread(ie, cpu));
	default:
		return (EINVAL);
	}
}