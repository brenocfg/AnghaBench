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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int* FDT_MAP_IRQ (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  arm_config_irq (int,int,int) ; 
 int gic_decode_fdt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*,int*) ; 
 int /*<<< orphan*/  stub1 (int,int,int) ; 

__attribute__((used)) static int
alpine_pic_decode_fdt(uint32_t iparent, uint32_t *intr, int *interrupt,
    int *trig, int *pol)
{
	int rv = 0;

	rv = gic_decode_fdt(iparent, intr, interrupt, trig, pol);
	if (rv == 0) {
		/* This was recognized as our PIC and decoded. */
		interrupt = FDT_MAP_IRQ(iparent, interrupt);

		/* Configure the interrupt if callback provided */
		if (arm_config_irq)
			(*arm_config_irq)(*interrupt, *trig, *pol);
	}
	return (rv);
}