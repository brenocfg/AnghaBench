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
struct xive_irq_data {int dummy; } ;

/* Variables and functions */
 struct xive_irq_data* irq_get_handler_data (unsigned int) ; 
 int /*<<< orphan*/  irq_set_handler_data (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct xive_irq_data*) ; 
 int /*<<< orphan*/  xive_cleanup_irq_data (struct xive_irq_data*) ; 

__attribute__((used)) static void xive_irq_free_data(unsigned int virq)
{
	struct xive_irq_data *xd = irq_get_handler_data(virq);

	if (!xd)
		return;
	irq_set_handler_data(virq, NULL);
	xive_cleanup_irq_data(xd);
	kfree(xd);
}