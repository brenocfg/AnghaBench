#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int exists; int /*<<< orphan*/  masked; int /*<<< orphan*/  chip; int /*<<< orphan*/ * domain; } ;
struct moxtet {int /*<<< orphan*/  dev_irq; TYPE_1__ irq; TYPE_2__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int BIT (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int MOXTET_NIRQS ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  irq_create_mapping (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * irq_domain_add_simple (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct moxtet*) ; 
 int /*<<< orphan*/  moxtet_irq_chip ; 
 int /*<<< orphan*/  moxtet_irq_domain ; 
 int /*<<< orphan*/  moxtet_irq_free (struct moxtet*) ; 
 int /*<<< orphan*/  moxtet_irq_thread_fn ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct moxtet*) ; 

__attribute__((used)) static int moxtet_irq_setup(struct moxtet *moxtet)
{
	int i, ret;

	moxtet->irq.domain = irq_domain_add_simple(moxtet->dev->of_node,
						   MOXTET_NIRQS, 0,
						   &moxtet_irq_domain, moxtet);
	if (moxtet->irq.domain == NULL) {
		dev_err(moxtet->dev, "Could not add IRQ domain\n");
		return -ENOMEM;
	}

	for (i = 0; i < MOXTET_NIRQS; ++i)
		if (moxtet->irq.exists & BIT(i))
			irq_create_mapping(moxtet->irq.domain, i);

	moxtet->irq.chip = moxtet_irq_chip;
	moxtet->irq.masked = ~0;

	ret = request_threaded_irq(moxtet->dev_irq, NULL, moxtet_irq_thread_fn,
				   IRQF_ONESHOT, "moxtet", moxtet);
	if (ret < 0)
		goto err_free;

	return 0;

err_free:
	moxtet_irq_free(moxtet);
	return ret;
}