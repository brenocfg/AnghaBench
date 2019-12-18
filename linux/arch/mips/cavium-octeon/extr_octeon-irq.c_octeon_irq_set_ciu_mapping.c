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
struct octeon_ciu_chip_data {int line; int bit; int gpio_line; } ;
struct irq_chip {int dummy; } ;
typedef  int /*<<< orphan*/  irq_flow_handler_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (int,struct irq_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (int,struct octeon_ciu_chip_data*) ; 
 struct octeon_ciu_chip_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int** octeon_irq_ciu_to_irq ; 

__attribute__((used)) static int octeon_irq_set_ciu_mapping(int irq, int line, int bit, int gpio_line,
				      struct irq_chip *chip,
				      irq_flow_handler_t handler)
{
	struct octeon_ciu_chip_data *cd;

	cd = kzalloc(sizeof(*cd), GFP_KERNEL);
	if (!cd)
		return -ENOMEM;

	irq_set_chip_and_handler(irq, chip, handler);

	cd->line = line;
	cd->bit = bit;
	cd->gpio_line = gpio_line;

	irq_set_chip_data(irq, cd);
	octeon_irq_ciu_to_irq[line][bit] = irq;
	return 0;
}