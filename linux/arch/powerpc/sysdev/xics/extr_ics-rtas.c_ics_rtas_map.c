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
struct ics {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 scalar_t__ WARN_ON (int) ; 
 unsigned int XICS_IPI ; 
 unsigned int XICS_IRQ_SPURIOUS ; 
 int /*<<< orphan*/  handle_fasteoi_irq ; 
 int /*<<< orphan*/  ibm_get_xive ; 
 int /*<<< orphan*/  ics_rtas ; 
 int /*<<< orphan*/  ics_rtas_irq_chip ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,int /*<<< orphan*/ *) ; 
 int rtas_call (int /*<<< orphan*/ ,int,int,int*,unsigned int) ; 
 scalar_t__ virq_to_hw (unsigned int) ; 

__attribute__((used)) static int ics_rtas_map(struct ics *ics, unsigned int virq)
{
	unsigned int hw_irq = (unsigned int)virq_to_hw(virq);
	int status[2];
	int rc;

	if (WARN_ON(hw_irq == XICS_IPI || hw_irq == XICS_IRQ_SPURIOUS))
		return -EINVAL;

	/* Check if RTAS knows about this interrupt */
	rc = rtas_call(ibm_get_xive, 1, 3, status, hw_irq);
	if (rc)
		return -ENXIO;

	irq_set_chip_and_handler(virq, &ics_rtas_irq_chip, handle_fasteoi_irq);
	irq_set_chip_data(virq, &ics_rtas);

	return 0;
}