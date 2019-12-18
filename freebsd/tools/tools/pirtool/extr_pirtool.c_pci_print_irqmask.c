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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void
pci_print_irqmask(uint16_t irqs)
{
	int i, first;

	if (irqs == 0) {
		printf("none");
		return;
	}
	first = 1;
	for (i = 0; i < 16; i++, irqs >>= 1)
		if (irqs & 1) {
			if (!first)
				printf(" ");
			else
				first = 0;
			printf("%d", i);
		}
}