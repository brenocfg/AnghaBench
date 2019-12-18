#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct bcma_device {TYPE_1__ id; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  bcma_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char) ; 

__attribute__((used)) static void bcma_core_mips_print_irq(struct bcma_device *dev, unsigned int irq)
{
	int i;
	static const char *irq_name[] = {"2(S)", "3", "4", "5", "6", "D", "I"};
	char interrupts[25];
	char *ints = interrupts;

	for (i = 0; i < ARRAY_SIZE(irq_name); i++)
		ints += sprintf(ints, " %s%c",
				irq_name[i], i == irq ? '*' : ' ');

	bcma_debug(dev->bus, "core 0x%04x, irq:%s\n", dev->id.id, interrupts);
}