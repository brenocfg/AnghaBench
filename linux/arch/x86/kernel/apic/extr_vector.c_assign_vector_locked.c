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
struct irq_data {int /*<<< orphan*/  irq; } ;
struct cpumask {int dummy; } ;
struct apic_chip_data {int has_reserved; unsigned int cpu; int vector; int /*<<< orphan*/  clist; scalar_t__ move_in_progress; } ;

/* Variables and functions */
 int EBUSY ; 
 struct apic_chip_data* apic_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  apic_update_irq_cfg (struct irq_data*,int,unsigned int) ; 
 int /*<<< orphan*/  apic_update_vector (struct irq_data*,int,unsigned int) ; 
 scalar_t__ cpu_online (unsigned int) ; 
 scalar_t__ cpumask_test_cpu (unsigned int,struct cpumask const*) ; 
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 
 int irq_matrix_alloc (int /*<<< orphan*/ ,struct cpumask const*,int,unsigned int*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_vector_alloc (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  vector_lock ; 
 int /*<<< orphan*/  vector_matrix ; 

__attribute__((used)) static int
assign_vector_locked(struct irq_data *irqd, const struct cpumask *dest)
{
	struct apic_chip_data *apicd = apic_chip_data(irqd);
	bool resvd = apicd->has_reserved;
	unsigned int cpu = apicd->cpu;
	int vector = apicd->vector;

	lockdep_assert_held(&vector_lock);

	/*
	 * If the current target CPU is online and in the new requested
	 * affinity mask, there is no point in moving the interrupt from
	 * one CPU to another.
	 */
	if (vector && cpu_online(cpu) && cpumask_test_cpu(cpu, dest))
		return 0;

	/*
	 * Careful here. @apicd might either have move_in_progress set or
	 * be enqueued for cleanup. Assigning a new vector would either
	 * leave a stale vector on some CPU around or in case of a pending
	 * cleanup corrupt the hlist.
	 */
	if (apicd->move_in_progress || !hlist_unhashed(&apicd->clist))
		return -EBUSY;

	vector = irq_matrix_alloc(vector_matrix, dest, resvd, &cpu);
	trace_vector_alloc(irqd->irq, vector, resvd, vector);
	if (vector < 0)
		return vector;
	apic_update_vector(irqd, vector, cpu);
	apic_update_irq_cfg(irqd, vector, cpu);

	return 0;
}