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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_DIVIL_SOFT_RESET ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static void cs5536_warm_reset(struct pci_dev *dev)
{
	/* writing 1 to the LSB of this MSR causes a hard reset */
	wrmsrl(MSR_DIVIL_SOFT_RESET, 1ULL);
	udelay(50); /* shouldn't get here but be safe and spin a while */
}