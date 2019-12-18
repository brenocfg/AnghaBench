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
typedef  union vfpf_tlvs {int dummy; } vfpf_tlvs ;
typedef  union pfvf_tlvs {int dummy; } pfvf_tlvs ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
typedef  size_t u16 ;
struct vfpf_first_tlv {scalar_t__ reply_address; } ;
struct ecore_vf_iov {scalar_t__ pf2vf_reply_phys; int /*<<< orphan*/ * offset; scalar_t__ pf2vf_reply; scalar_t__ vf2pf_request; int /*<<< orphan*/  mutex; } ;
struct ecore_hwfn {struct ecore_vf_iov* vf_iov_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECORE_MSG_IOV ; 
 int /*<<< orphan*/  OSAL_MEMSET (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OSAL_MUTEX_ACQUIRE (int /*<<< orphan*/ *) ; 
 void* ecore_add_tlv (int /*<<< orphan*/ **,size_t,size_t) ; 
 int /*<<< orphan*/ * ecore_channel_tlvs_string ; 

__attribute__((used)) static void *ecore_vf_pf_prep(struct ecore_hwfn *p_hwfn,
			      u16 type, u16 length)
{
	struct ecore_vf_iov *p_iov = p_hwfn->vf_iov_info;
	void *p_tlv;

	/* This lock is released when we receive PF's response
	 * in ecore_send_msg2pf().
	 * So, ecore_vf_pf_prep() and ecore_send_msg2pf()
	 * must come in sequence.
	 */
	OSAL_MUTEX_ACQUIRE(&(p_iov->mutex));

	DP_VERBOSE(p_hwfn, ECORE_MSG_IOV, "preparing to send %s tlv over vf pf channel\n",
		   ecore_channel_tlvs_string[type]);

	/* Reset Requst offset */
	p_iov->offset = (u8 *)p_iov->vf2pf_request;

	/* Clear mailbox - both request and reply */
	OSAL_MEMSET(p_iov->vf2pf_request, 0,
		    sizeof(union vfpf_tlvs));
	OSAL_MEMSET(p_iov->pf2vf_reply, 0,
		    sizeof(union pfvf_tlvs));

	/* Init type and length */
	p_tlv = ecore_add_tlv(&p_iov->offset, type, length);

	/* Init first tlv header */
	((struct vfpf_first_tlv *)p_tlv)->reply_address =
		(u64)p_iov->pf2vf_reply_phys;

	return p_tlv;
}