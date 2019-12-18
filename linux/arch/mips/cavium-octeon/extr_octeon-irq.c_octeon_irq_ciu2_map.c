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
typedef  int irq_hw_number_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  octeon_irq_chip_ciu2 ; 
 int /*<<< orphan*/  octeon_irq_chip_ciu2_edge ; 
 scalar_t__ octeon_irq_ciu2_is_edge (unsigned int,unsigned int) ; 
 scalar_t__** octeon_irq_ciu_to_irq ; 
 int /*<<< orphan*/  octeon_irq_set_ciu_mapping (unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int octeon_irq_ciu2_map(struct irq_domain *d,
			       unsigned int virq, irq_hw_number_t hw)
{
	unsigned int line = hw >> 6;
	unsigned int bit = hw & 63;

	/*
	 * Don't map irq if it is reserved for GPIO.
	 * (Line 7 are the GPIO lines.)
	 */
	if (line == 7)
		return 0;

	if (line > 7 || octeon_irq_ciu_to_irq[line][bit] != 0)
		return -EINVAL;

	if (octeon_irq_ciu2_is_edge(line, bit))
		octeon_irq_set_ciu_mapping(virq, line, bit, 0,
					   &octeon_irq_chip_ciu2_edge,
					   handle_edge_irq);
	else
		octeon_irq_set_ciu_mapping(virq, line, bit, 0,
					   &octeon_irq_chip_ciu2,
					   handle_level_irq);

	return 0;
}