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
struct intr_irqsrc {scalar_t__ isrc_dev; int /*<<< orphan*/  isrc_cpu; int /*<<< orphan*/  isrc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SETOF (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  INTR_ISRCF_BOUND ; 
 int NOCPU ; 
 int PIC_BIND_INTR (scalar_t__,struct intr_irqsrc*) ; 
 scalar_t__ intr_irq_root_dev ; 
 scalar_t__ irq_assign_cpu ; 
 int /*<<< orphan*/  isrc_table_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
intr_isrc_assign_cpu(void *arg, int cpu)
{
#ifdef SMP
	struct intr_irqsrc *isrc = arg;
	int error;

	if (isrc->isrc_dev != intr_irq_root_dev)
		return (EINVAL);

	mtx_lock(&isrc_table_lock);
	if (cpu == NOCPU) {
		CPU_ZERO(&isrc->isrc_cpu);
		isrc->isrc_flags &= ~INTR_ISRCF_BOUND;
	} else {
		CPU_SETOF(cpu, &isrc->isrc_cpu);
		isrc->isrc_flags |= INTR_ISRCF_BOUND;
	}

	/*
	 * In NOCPU case, it's up to PIC to either leave ISRC on same CPU or
	 * re-balance it to another CPU or enable it on more CPUs. However,
	 * PIC is expected to change isrc_cpu appropriately to keep us well
	 * informed if the call is successful.
	 */
	if (irq_assign_cpu) {
		error = PIC_BIND_INTR(isrc->isrc_dev, isrc);
		if (error) {
			CPU_ZERO(&isrc->isrc_cpu);
			mtx_unlock(&isrc_table_lock);
			return (error);
		}
	}
	mtx_unlock(&isrc_table_lock);
	return (0);
#else
	return (EOPNOTSUPP);
#endif
}