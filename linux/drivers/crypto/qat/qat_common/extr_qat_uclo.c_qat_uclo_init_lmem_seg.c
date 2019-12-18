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
struct icp_qat_uof_initmem {int dummy; } ;
struct icp_qat_uclo_objhandle {int /*<<< orphan*/ * lm_init_tab; } ;
struct icp_qat_fw_loader_handle {struct icp_qat_uclo_objhandle* obj_handle; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ICP_QAT_UCLO_MAX_LMEM_REG ; 
 scalar_t__ qat_uclo_create_batch_init_list (struct icp_qat_fw_loader_handle*,struct icp_qat_uof_initmem*,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ qat_uclo_fetch_initmem_ae (struct icp_qat_fw_loader_handle*,struct icp_qat_uof_initmem*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int qat_uclo_init_lmem_seg(struct icp_qat_fw_loader_handle *handle,
				  struct icp_qat_uof_initmem *init_mem)
{
	struct icp_qat_uclo_objhandle *obj_handle = handle->obj_handle;
	unsigned int ae;

	if (qat_uclo_fetch_initmem_ae(handle, init_mem,
				      ICP_QAT_UCLO_MAX_LMEM_REG, &ae))
		return -EINVAL;
	if (qat_uclo_create_batch_init_list(handle, init_mem, ae,
					    &obj_handle->lm_init_tab[ae]))
		return -EINVAL;
	return 0;
}