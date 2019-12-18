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
struct of_phandle_args {int args_count; int* args; int /*<<< orphan*/  np; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct TYPE_2__ {scalar_t__ of_node; } ;
struct bcma_device {int /*<<< orphan*/  addr; TYPE_1__ dev; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int of_irq_parse_one (scalar_t__,int,struct of_phandle_args*) ; 
 int of_irq_parse_raw (int /*<<< orphan*/ *,struct of_phandle_args*) ; 

__attribute__((used)) static int bcma_of_irq_parse(struct device *parent,
			     struct bcma_device *core,
			     struct of_phandle_args *out_irq, int num)
{
	__be32 laddr[1];
	int rc;

	if (core->dev.of_node) {
		rc = of_irq_parse_one(core->dev.of_node, num, out_irq);
		if (!rc)
			return rc;
	}

	out_irq->np = parent->of_node;
	out_irq->args_count = 1;
	out_irq->args[0] = num;

	laddr[0] = cpu_to_be32(core->addr);
	return of_irq_parse_raw(laddr, out_irq);
}