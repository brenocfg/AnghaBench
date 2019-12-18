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
struct mp_chip_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ __add_pin_to_irq_node (struct mp_chip_data*,int,int,int) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void add_pin_to_irq_node(struct mp_chip_data *data,
				int node, int apic, int pin)
{
	if (__add_pin_to_irq_node(data, node, apic, pin))
		panic("IO-APIC: failed to add irq-pin. Can not proceed\n");
}