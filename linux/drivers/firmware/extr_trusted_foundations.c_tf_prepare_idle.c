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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TF_CPU_PM ; 
 int /*<<< orphan*/  TF_CPU_PM_S1 ; 
 int /*<<< orphan*/  TF_CPU_PM_S1_NOFLUSH_L2 ; 
 int /*<<< orphan*/  TF_CPU_PM_S2 ; 
 int /*<<< orphan*/  TF_CPU_PM_S2_NO_MC_CLK ; 
 int /*<<< orphan*/  TF_CPU_PM_S3 ; 
#define  TF_PM_MODE_LP0 132 
#define  TF_PM_MODE_LP1 131 
#define  TF_PM_MODE_LP1_NO_MC_CLK 130 
#define  TF_PM_MODE_LP2 129 
#define  TF_PM_MODE_LP2_NOFLUSH_L2 128 
 int /*<<< orphan*/  cpu_boot_addr ; 
 int /*<<< orphan*/  tf_generic_smc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tf_prepare_idle(unsigned long mode)
{
	switch (mode) {
	case TF_PM_MODE_LP0:
		tf_generic_smc(TF_CPU_PM, TF_CPU_PM_S3, cpu_boot_addr);
		break;

	case TF_PM_MODE_LP1:
		tf_generic_smc(TF_CPU_PM, TF_CPU_PM_S2, cpu_boot_addr);
		break;

	case TF_PM_MODE_LP1_NO_MC_CLK:
		tf_generic_smc(TF_CPU_PM, TF_CPU_PM_S2_NO_MC_CLK,
			       cpu_boot_addr);
		break;

	case TF_PM_MODE_LP2:
		tf_generic_smc(TF_CPU_PM, TF_CPU_PM_S1, cpu_boot_addr);
		break;

	case TF_PM_MODE_LP2_NOFLUSH_L2:
		tf_generic_smc(TF_CPU_PM, TF_CPU_PM_S1_NOFLUSH_L2,
			       cpu_boot_addr);
		break;

	default:
		return -EINVAL;
	}

	return 0;
}