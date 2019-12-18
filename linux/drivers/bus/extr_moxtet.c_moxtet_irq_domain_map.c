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
struct TYPE_2__ {int exists; int /*<<< orphan*/  chip; } ;
struct moxtet {TYPE_1__ irq; int /*<<< orphan*/  dev; } ;
struct irq_domain {struct moxtet* host_data; } ;
typedef  scalar_t__ irq_hw_number_t ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 int EINVAL ; 
 scalar_t__ MOXTET_NIRQS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,struct moxtet*) ; 

__attribute__((used)) static int moxtet_irq_domain_map(struct irq_domain *d, unsigned int irq,
				 irq_hw_number_t hw)
{
	struct moxtet *moxtet = d->host_data;

	if (hw >= MOXTET_NIRQS || !(moxtet->irq.exists & BIT(hw))) {
		dev_err(moxtet->dev, "Invalid hw irq number\n");
		return -EINVAL;
	}

	irq_set_chip_data(irq, d->host_data);
	irq_set_chip_and_handler(irq, &moxtet->irq.chip, handle_level_irq);

	return 0;
}