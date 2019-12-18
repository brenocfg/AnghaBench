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
struct apic_chip_data {unsigned int vector; unsigned int prev_vector; int /*<<< orphan*/  clist; scalar_t__ move_in_progress; int /*<<< orphan*/  prev_cpu; int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  VECTOR_SHUTDOWN ; 
 struct apic_chip_data* apic_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_matrix_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 int irqd_affinity_is_managed (struct irq_data*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * per_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_vector_clear (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vector_irq ; 
 int /*<<< orphan*/  vector_lock ; 
 int /*<<< orphan*/  vector_matrix ; 

__attribute__((used)) static void clear_irq_vector(struct irq_data *irqd)
{
	struct apic_chip_data *apicd = apic_chip_data(irqd);
	bool managed = irqd_affinity_is_managed(irqd);
	unsigned int vector = apicd->vector;

	lockdep_assert_held(&vector_lock);

	if (!vector)
		return;

	trace_vector_clear(irqd->irq, vector, apicd->cpu, apicd->prev_vector,
			   apicd->prev_cpu);

	per_cpu(vector_irq, apicd->cpu)[vector] = VECTOR_SHUTDOWN;
	irq_matrix_free(vector_matrix, apicd->cpu, vector, managed);
	apicd->vector = 0;

	/* Clean up move in progress */
	vector = apicd->prev_vector;
	if (!vector)
		return;

	per_cpu(vector_irq, apicd->prev_cpu)[vector] = VECTOR_SHUTDOWN;
	irq_matrix_free(vector_matrix, apicd->prev_cpu, vector, managed);
	apicd->prev_vector = 0;
	apicd->move_in_progress = 0;
	hlist_del_init(&apicd->clist);
}