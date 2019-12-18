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
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc8xx_pic ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpc8xx_pic_host_map(struct irq_domain *h, unsigned int virq,
			  irq_hw_number_t hw)
{
	pr_debug("mpc8xx_pic_host_map(%d, 0x%lx)\n", virq, hw);

	/* Set default irq handle */
	irq_set_chip_and_handler(virq, &mpc8xx_pic, handle_level_irq);
	return 0;
}