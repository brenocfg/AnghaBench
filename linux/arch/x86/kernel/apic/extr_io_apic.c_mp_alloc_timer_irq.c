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
struct irq_domain {int dummy; } ;
struct irq_alloc_info {int ioapic_pin; int /*<<< orphan*/  ioapic_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int alloc_isa_irq_from_domain (struct irq_domain*,int /*<<< orphan*/ ,int,int,struct irq_alloc_info*) ; 
 int /*<<< orphan*/  ioapic_mutex ; 
 int /*<<< orphan*/  ioapic_set_alloc_attr (struct irq_alloc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct irq_domain* mp_ioapic_irqdomain (int) ; 
 int /*<<< orphan*/  mpc_ioapic_id (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mp_alloc_timer_irq(int ioapic, int pin)
{
	int irq = -1;
	struct irq_domain *domain = mp_ioapic_irqdomain(ioapic);

	if (domain) {
		struct irq_alloc_info info;

		ioapic_set_alloc_attr(&info, NUMA_NO_NODE, 0, 0);
		info.ioapic_id = mpc_ioapic_id(ioapic);
		info.ioapic_pin = pin;
		mutex_lock(&ioapic_mutex);
		irq = alloc_isa_irq_from_domain(domain, 0, ioapic, pin, &info);
		mutex_unlock(&ioapic_mutex);
	}

	return irq;
}