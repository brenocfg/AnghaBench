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
typedef  size_t u32 ;
typedef  size_t u16 ;
struct ecore_iwarp_info {size_t max_num_partial_fpdus; struct ecore_iwarp_fpdu* partial_fpdus; } ;
struct ecore_iwarp_fpdu {int dummy; } ;
struct ecore_hwfn {TYPE_1__* p_rdma_info; } ;
struct TYPE_2__ {struct ecore_iwarp_info iwarp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*,size_t,size_t) ; 
 struct ecore_iwarp_fpdu* OSAL_NULL ; 
 int /*<<< orphan*/  PROTOCOLID_IWARP ; 
 size_t ecore_cxt_get_proto_cid_start (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ecore_iwarp_fpdu *
ecore_iwarp_get_curr_fpdu(struct ecore_hwfn *p_hwfn, u16 cid)
{
	struct ecore_iwarp_info *iwarp_info = &p_hwfn->p_rdma_info->iwarp;
	struct ecore_iwarp_fpdu *partial_fpdu;
	u32 idx = cid - ecore_cxt_get_proto_cid_start(p_hwfn, PROTOCOLID_IWARP);

	if (idx >= iwarp_info->max_num_partial_fpdus) {
		DP_ERR(p_hwfn, "Invalid cid %x max_num_partial_fpdus=%x\n", cid,
		       iwarp_info->max_num_partial_fpdus);
		return OSAL_NULL;
	}

	partial_fpdu = &iwarp_info->partial_fpdus[idx];

	return partial_fpdu;
}