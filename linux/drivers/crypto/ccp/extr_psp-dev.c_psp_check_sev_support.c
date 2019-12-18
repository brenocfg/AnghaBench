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
struct psp_device {int /*<<< orphan*/  dev; TYPE_1__* vdata; scalar_t__ io_regs; } ;
struct TYPE_2__ {scalar_t__ feature_reg; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int ioread32 (scalar_t__) ; 

__attribute__((used)) static int psp_check_sev_support(struct psp_device *psp)
{
	/* Check if device supports SEV feature */
	if (!(ioread32(psp->io_regs + psp->vdata->feature_reg) & 1)) {
		dev_dbg(psp->dev, "psp does not support SEV\n");
		return -ENODEV;
	}

	return 0;
}