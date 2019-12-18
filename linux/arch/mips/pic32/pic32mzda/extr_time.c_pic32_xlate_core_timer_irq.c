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
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_CORE_TIMER_INTERRUPT ; 
 scalar_t__ WARN_ON (int) ; 
 unsigned int irq_create_mapping (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 struct device_node* of_find_matching_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pic32_infra_match ; 

__attribute__((used)) static unsigned int pic32_xlate_core_timer_irq(void)
{
	static struct device_node *node;
	unsigned int irq;

	node = of_find_matching_node(NULL, pic32_infra_match);

	if (WARN_ON(!node))
		goto default_map;

	irq = irq_of_parse_and_map(node, 0);
	if (!irq)
		goto default_map;

	return irq;

default_map:

	return irq_create_mapping(NULL, DEFAULT_CORE_TIMER_INTERRUPT);
}