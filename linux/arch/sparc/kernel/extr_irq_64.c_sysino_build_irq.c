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
typedef  int /*<<< orphan*/  u32 ;
struct irq_chip {int dummy; } ;

/* Variables and functions */
 unsigned int sun4v_build_common (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,struct irq_chip*) ; 
 int /*<<< orphan*/  sysino_handler_data ; 
 int /*<<< orphan*/  sysino_set_bucket (unsigned int) ; 

__attribute__((used)) static unsigned int sysino_build_irq(u32 devhandle, unsigned int devino,
				     struct irq_chip *chip)
{
	unsigned int irq;

	irq = sun4v_build_common(devhandle, devino, sysino_handler_data, chip);
	if (!irq)
		goto out;

	sysino_set_bucket(irq);
out:
	return irq;
}