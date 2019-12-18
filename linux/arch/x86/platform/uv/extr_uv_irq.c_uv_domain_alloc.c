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
struct uv_irq_2_mmr_pnode {int /*<<< orphan*/  offset; int /*<<< orphan*/  pnode; } ;
struct irq_domain {int dummy; } ;
struct irq_data {int dummy; } ;
struct irq_alloc_info {scalar_t__ type; scalar_t__ uv_limit; int /*<<< orphan*/  uv_name; int /*<<< orphan*/  uv_offset; int /*<<< orphan*/  uv_blade; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQ_MOVE_PCNTXT ; 
 int /*<<< orphan*/  IRQ_NO_BALANCING ; 
 scalar_t__ UV_AFFINITY_CPU ; 
 scalar_t__ X86_IRQ_ALLOC_TYPE_UV ; 
 int /*<<< orphan*/  handle_percpu_irq ; 
 int /*<<< orphan*/  irq_data_get_node (struct irq_data*) ; 
 int irq_domain_alloc_irqs_parent (struct irq_domain*,unsigned int,unsigned int,void*) ; 
 struct irq_data* irq_domain_get_irq_data (struct irq_domain*,unsigned int) ; 
 int /*<<< orphan*/  irq_domain_set_info (struct irq_domain*,unsigned int,unsigned int,int /*<<< orphan*/ *,struct uv_irq_2_mmr_pnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_status_flags (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct uv_irq_2_mmr_pnode*) ; 
 struct uv_irq_2_mmr_pnode* kmalloc_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_blade_to_pnode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_irq_chip ; 

__attribute__((used)) static int uv_domain_alloc(struct irq_domain *domain, unsigned int virq,
			   unsigned int nr_irqs, void *arg)
{
	struct uv_irq_2_mmr_pnode *chip_data;
	struct irq_alloc_info *info = arg;
	struct irq_data *irq_data = irq_domain_get_irq_data(domain, virq);
	int ret;

	if (nr_irqs > 1 || !info || info->type != X86_IRQ_ALLOC_TYPE_UV)
		return -EINVAL;

	chip_data = kmalloc_node(sizeof(*chip_data), GFP_KERNEL,
				 irq_data_get_node(irq_data));
	if (!chip_data)
		return -ENOMEM;

	ret = irq_domain_alloc_irqs_parent(domain, virq, nr_irqs, arg);
	if (ret >= 0) {
		if (info->uv_limit == UV_AFFINITY_CPU)
			irq_set_status_flags(virq, IRQ_NO_BALANCING);
		else
			irq_set_status_flags(virq, IRQ_MOVE_PCNTXT);

		chip_data->pnode = uv_blade_to_pnode(info->uv_blade);
		chip_data->offset = info->uv_offset;
		irq_domain_set_info(domain, virq, virq, &uv_irq_chip, chip_data,
				    handle_percpu_irq, NULL, info->uv_name);
	} else {
		kfree(chip_data);
	}

	return ret;
}