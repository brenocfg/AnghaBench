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
typedef  int /*<<< orphan*/  u32 ;
struct sata_dwc_device {TYPE_1__* sata_dwc_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  intpr; } ;

/* Variables and functions */
 int /*<<< orphan*/  sata_dwc_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sata_dwc_writel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clear_interrupt_bit(struct sata_dwc_device *hsdev, u32 bit)
{
	sata_dwc_writel(&hsdev->sata_dwc_regs->intpr,
			sata_dwc_readl(&hsdev->sata_dwc_regs->intpr));
}