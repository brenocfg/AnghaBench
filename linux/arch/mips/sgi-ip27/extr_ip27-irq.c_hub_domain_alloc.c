#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct irq_domain {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  affinity; int /*<<< orphan*/  node; } ;
struct irq_desc {TYPE_1__ irq_common_data; } ;
struct irq_alloc_info {int /*<<< orphan*/  nasid; } ;
struct hub_irq_data {int dummy; } ;
struct hub_data {int /*<<< orphan*/  h_cpus; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NASID_TO_COMPACT_NODEID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REMOTE_HUB_CLR_INTR (int /*<<< orphan*/ ,int) ; 
 int alloc_level () ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_level_irq ; 
 struct hub_data* hub_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hub_irq_type ; 
 int /*<<< orphan*/  irq_domain_set_info (struct irq_domain*,unsigned int,int,int /*<<< orphan*/ *,struct hub_irq_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 
 int /*<<< orphan*/  kfree (struct hub_irq_data*) ; 
 struct hub_irq_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_hub_mask (struct hub_irq_data*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int hub_domain_alloc(struct irq_domain *domain, unsigned int virq,
			    unsigned int nr_irqs, void *arg)
{
	struct irq_alloc_info *info = arg;
	struct hub_irq_data *hd;
	struct hub_data *hub;
	struct irq_desc *desc;
	int swlevel;

	if (nr_irqs > 1 || !info)
		return -EINVAL;

	hd = kzalloc(sizeof(*hd), GFP_KERNEL);
	if (!hd)
		return -ENOMEM;

	swlevel = alloc_level();
	if (unlikely(swlevel < 0)) {
		kfree(hd);
		return -EAGAIN;
	}
	irq_domain_set_info(domain, virq, swlevel, &hub_irq_type, hd,
			    handle_level_irq, NULL, NULL);

	/* use CPU connected to nearest hub */
	hub = hub_data(NASID_TO_COMPACT_NODEID(info->nasid));
	setup_hub_mask(hd, &hub->h_cpus);

	/* Make sure it's not already pending when we connect it. */
	REMOTE_HUB_CLR_INTR(info->nasid, swlevel);

	desc = irq_to_desc(virq);
	desc->irq_common_data.node = info->nasid;
	cpumask_copy(desc->irq_common_data.affinity, &hub->h_cpus);

	return 0;
}