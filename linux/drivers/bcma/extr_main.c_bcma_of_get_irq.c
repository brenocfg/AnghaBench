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
struct of_phandle_args {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct bcma_device {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF_IRQ ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_debug (int /*<<< orphan*/ ,char*,int) ; 
 int bcma_of_irq_parse (struct device*,struct bcma_device*,struct of_phandle_args*,int) ; 
 unsigned int irq_create_of_mapping (struct of_phandle_args*) ; 

__attribute__((used)) static unsigned int bcma_of_get_irq(struct device *parent,
				    struct bcma_device *core, int num)
{
	struct of_phandle_args out_irq;
	int ret;

	if (!IS_ENABLED(CONFIG_OF_IRQ) || !parent->of_node)
		return 0;

	ret = bcma_of_irq_parse(parent, core, &out_irq, num);
	if (ret) {
		bcma_debug(core->bus, "bcma_of_get_irq() failed with rc=%d\n",
			   ret);
		return 0;
	}

	return irq_create_of_mapping(&out_irq);
}