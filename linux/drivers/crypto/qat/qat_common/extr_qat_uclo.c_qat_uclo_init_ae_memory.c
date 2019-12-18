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
struct icp_qat_uof_initmem {int region; } ;
struct icp_qat_fw_loader_handle {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ICP_QAT_UOF_LMEM_REGION 129 
#define  ICP_QAT_UOF_UMEM_REGION 128 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  qat_uclo_init_lmem_seg (struct icp_qat_fw_loader_handle*,struct icp_qat_uof_initmem*) ; 
 int /*<<< orphan*/  qat_uclo_init_umem_seg (struct icp_qat_fw_loader_handle*,struct icp_qat_uof_initmem*) ; 

__attribute__((used)) static int qat_uclo_init_ae_memory(struct icp_qat_fw_loader_handle *handle,
				   struct icp_qat_uof_initmem *init_mem)
{
	switch (init_mem->region) {
	case ICP_QAT_UOF_LMEM_REGION:
		if (qat_uclo_init_lmem_seg(handle, init_mem))
			return -EINVAL;
		break;
	case ICP_QAT_UOF_UMEM_REGION:
		if (qat_uclo_init_umem_seg(handle, init_mem))
			return -EINVAL;
		break;
	default:
		pr_err("QAT: initmem region error. region type=0x%x\n",
		       init_mem->region);
		return -EINVAL;
	}
	return 0;
}