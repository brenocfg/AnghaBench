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
struct qcom_scm_desc {int /*<<< orphan*/  arginfo; void** args; int /*<<< orphan*/  member_0; } ;
struct device {int dummy; } ;
struct arm_smccc_res {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QCOM_SCM_ARGS (int) ; 
 void* QCOM_SCM_SET_DLOAD_MODE ; 
 int /*<<< orphan*/  QCOM_SCM_SVC_BOOT ; 
 int qcom_scm_call (struct device*,int /*<<< orphan*/ ,void*,struct qcom_scm_desc*,struct arm_smccc_res*) ; 

int __qcom_scm_set_dload_mode(struct device *dev, bool enable)
{
	struct qcom_scm_desc desc = {0};
	struct arm_smccc_res res;

	desc.args[0] = QCOM_SCM_SET_DLOAD_MODE;
	desc.args[1] = enable ? QCOM_SCM_SET_DLOAD_MODE : 0;
	desc.arginfo = QCOM_SCM_ARGS(2);

	return qcom_scm_call(dev, QCOM_SCM_SVC_BOOT, QCOM_SCM_SET_DLOAD_MODE,
			     &desc, &res);
}