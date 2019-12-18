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
struct platform_device {int dummy; } ;
struct dfl_feature {int dummy; } ;

/* Variables and functions */
#define  DFL_FPGA_FME_PORT_PR 128 
 long ENODEV ; 
 long fme_pr (struct platform_device*,unsigned long) ; 

__attribute__((used)) static long fme_pr_ioctl(struct platform_device *pdev,
			 struct dfl_feature *feature,
			 unsigned int cmd, unsigned long arg)
{
	long ret;

	switch (cmd) {
	case DFL_FPGA_FME_PORT_PR:
		ret = fme_pr(pdev, arg);
		break;
	default:
		ret = -ENODEV;
	}

	return ret;
}