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
struct qcom_scm_desc {size_t* args; int /*<<< orphan*/  arginfo; int /*<<< orphan*/  member_0; } ;
struct device {int dummy; } ;
struct arm_smccc_res {int a1; } ;
typedef  void* phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  QCOM_MEM_PROT_ASSIGN_ID ; 
 int /*<<< orphan*/  QCOM_SCM_ARGS (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QCOM_SCM_RO ; 
 int /*<<< orphan*/  QCOM_SCM_SVC_MP ; 
 int /*<<< orphan*/  QCOM_SCM_VAL ; 
 int qcom_scm_call (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qcom_scm_desc*,struct arm_smccc_res*) ; 

int __qcom_scm_assign_mem(struct device *dev, phys_addr_t mem_region,
			  size_t mem_sz, phys_addr_t src, size_t src_sz,
			  phys_addr_t dest, size_t dest_sz)
{
	int ret;
	struct qcom_scm_desc desc = {0};
	struct arm_smccc_res res;

	desc.args[0] = mem_region;
	desc.args[1] = mem_sz;
	desc.args[2] = src;
	desc.args[3] = src_sz;
	desc.args[4] = dest;
	desc.args[5] = dest_sz;
	desc.args[6] = 0;

	desc.arginfo = QCOM_SCM_ARGS(7, QCOM_SCM_RO, QCOM_SCM_VAL,
				     QCOM_SCM_RO, QCOM_SCM_VAL, QCOM_SCM_RO,
				     QCOM_SCM_VAL, QCOM_SCM_VAL);

	ret = qcom_scm_call(dev, QCOM_SCM_SVC_MP,
			    QCOM_MEM_PROT_ASSIGN_ID,
			    &desc, &res);

	return ret ? : res.a1;
}