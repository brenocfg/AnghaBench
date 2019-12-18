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
struct s10_svc_softc {int (* callfn ) (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arm_smccc_res*) ;} ;
struct arm_smccc_res {int dummy; } ;
typedef  scalar_t__ register_t ;

/* Variables and functions */
 scalar_t__ INTEL_SIP_SMC_FPGA_CONFIG_COMPLETED_WRITE ; 
 int INTEL_SIP_SMC_FPGA_CONFIG_STATUS_BUSY ; 
 int stub1 (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arm_smccc_res*) ; 

__attribute__((used)) static int
s10_data_claim(struct s10_svc_softc *sc)
{
	struct arm_smccc_res res;
	register_t a0, a1, a2;
	int ret;

	ret = 0;

	while (1) {
		a0 = INTEL_SIP_SMC_FPGA_CONFIG_COMPLETED_WRITE;
		a1 = 0;
		a2 = 0;

		ret = sc->callfn(a0, a1, a2, 0, 0, 0, 0, 0, &res);
		if (ret == INTEL_SIP_SMC_FPGA_CONFIG_STATUS_BUSY)
			continue;

		break;
	}

	return (ret);
}