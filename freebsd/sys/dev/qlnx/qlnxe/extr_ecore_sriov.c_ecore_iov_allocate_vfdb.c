#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union vfpf_tlvs {int dummy; } vfpf_tlvs ;
typedef  union pfvf_tlvs {int dummy; } pfvf_tlvs ;
typedef  int u16 ;
struct ecore_pf_iov {int mbx_msg_size; void* mbx_msg_virt_addr; int mbx_reply_size; void* mbx_reply_virt_addr; int bulletins_size; void* p_bulletins; scalar_t__ bulletins_phys; scalar_t__ mbx_reply_phys_addr; scalar_t__ mbx_msg_phys_addr; } ;
struct ecore_hwfn {TYPE_2__* p_dev; struct ecore_pf_iov* pf_iov_info; } ;
struct ecore_bulletin_content {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_4__ {TYPE_1__* p_iov_info; } ;
struct TYPE_3__ {int total_vfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,void*,...) ; 
 int /*<<< orphan*/  ECORE_MSG_IOV ; 
 int ECORE_NOMEM ; 
 int ECORE_SUCCESS ; 
 void* OSAL_DMA_ALLOC_COHERENT (TYPE_2__*,scalar_t__*,int) ; 

__attribute__((used)) static enum _ecore_status_t ecore_iov_allocate_vfdb(struct ecore_hwfn *p_hwfn)
{
	struct ecore_pf_iov *p_iov_info = p_hwfn->pf_iov_info;
	void **p_v_addr;
	u16 num_vfs = 0;

	num_vfs = p_hwfn->p_dev->p_iov_info->total_vfs;

	DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
		   "ecore_iov_allocate_vfdb for %d VFs\n", num_vfs);

	/* Allocate PF Mailbox buffer (per-VF) */
	p_iov_info->mbx_msg_size = sizeof(union vfpf_tlvs) * num_vfs;
	p_v_addr = &p_iov_info->mbx_msg_virt_addr;
	*p_v_addr = OSAL_DMA_ALLOC_COHERENT(p_hwfn->p_dev,
					    &p_iov_info->mbx_msg_phys_addr,
					    p_iov_info->mbx_msg_size);
	if (!*p_v_addr)
		return ECORE_NOMEM;

	/* Allocate PF Mailbox Reply buffer (per-VF) */
	p_iov_info->mbx_reply_size = sizeof(union pfvf_tlvs) * num_vfs;
	p_v_addr = &p_iov_info->mbx_reply_virt_addr;
	*p_v_addr = OSAL_DMA_ALLOC_COHERENT(p_hwfn->p_dev,
					    &p_iov_info->mbx_reply_phys_addr,
					    p_iov_info->mbx_reply_size);
	if (!*p_v_addr)
		return ECORE_NOMEM;

	p_iov_info->bulletins_size = sizeof(struct ecore_bulletin_content) *
				     num_vfs;
	p_v_addr = &p_iov_info->p_bulletins;
	*p_v_addr = OSAL_DMA_ALLOC_COHERENT(p_hwfn->p_dev,
					    &p_iov_info->bulletins_phys,
					    p_iov_info->bulletins_size);
	if (!*p_v_addr)
		return ECORE_NOMEM;

	DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
		   "PF's Requests mailbox [%p virt 0x%llx phys],  Response mailbox [%p virt 0x%llx phys] Bulletins [%p virt 0x%llx phys]\n",
		   p_iov_info->mbx_msg_virt_addr,
		   (unsigned long long)p_iov_info->mbx_msg_phys_addr,
		   p_iov_info->mbx_reply_virt_addr,
		   (unsigned long long)p_iov_info->mbx_reply_phys_addr,
		   p_iov_info->p_bulletins,
		   (unsigned long long)p_iov_info->bulletins_phys);

	return ECORE_SUCCESS;
}