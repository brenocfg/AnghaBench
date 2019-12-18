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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 unsigned int FSR_EXTERNAL ; 
 unsigned int FSR_IMPRECISE ; 
 unsigned int FSR_READ ; 

__attribute__((used)) static int bcm5301x_abort_handler(unsigned long addr, unsigned int fsr,
				  struct pt_regs *regs)
{
	/*
	 * We want to ignore aborts forwarded from the PCIe bus that are
	 * expected and shouldn't really be passed by the PCIe controller.
	 * The biggest disadvantage is the same FSR code may be reported when
	 * reading non-existing APB register and we shouldn't ignore that.
	 */
	if (fsr == (FSR_EXTERNAL | FSR_READ | FSR_IMPRECISE))
		return 0;

	return 1;
}