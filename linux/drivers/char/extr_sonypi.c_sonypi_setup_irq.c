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
struct sonypi_irq_list {int /*<<< orphan*/  bits; scalar_t__ irq; } ;
struct sonypi_device {int /*<<< orphan*/  bits; scalar_t__ irq; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sonypi_irq ; 

__attribute__((used)) static int sonypi_setup_irq(struct sonypi_device *dev,
				      const struct sonypi_irq_list *irq_list)
{
	while (irq_list->irq) {

		if (!request_irq(irq_list->irq, sonypi_irq,
				 IRQF_SHARED, "sonypi", sonypi_irq)) {
			dev->irq = irq_list->irq;
			dev->bits = irq_list->bits;
			return 0;
		}
		irq_list++;
	}

	return -EBUSY;
}