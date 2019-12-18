#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct ecore_hwfn {struct ecore_cxt_mngr* p_cxt_mngr; } ;
struct ecore_cxt_mngr {TYPE_3__* ilt_shadow; TYPE_2__* clients; } ;
struct ecore_cxt_info {size_t iid; int type; int /*<<< orphan*/ * p_cxt; } ;
struct ecore_cid_acquired_map {int dummy; } ;
typedef  enum protocol_type { ____Placeholder_protocol_type } protocol_type ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_6__ {scalar_t__ p_virt; } ;
struct TYPE_4__ {size_t val; } ;
struct TYPE_5__ {TYPE_1__ p_size; } ;

/* Variables and functions */
 size_t CONN_CXT_SIZE (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int,char*,size_t,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ECORE_CXT_PF_CID ; 
 int ECORE_INVAL ; 
 int ECORE_MSG_CXT ; 
 int ECORE_MSG_ILT ; 
 int ECORE_SUCCESS ; 
 size_t ILT_CLI_CDUC ; 
 size_t ILT_PAGE_IN_BYTES (size_t) ; 
 struct ecore_cid_acquired_map* OSAL_NULL ; 
 int ecore_cxt_test_cid_acquired (struct ecore_hwfn*,size_t,int /*<<< orphan*/ ,int*,struct ecore_cid_acquired_map**) ; 

enum _ecore_status_t ecore_cxt_get_cid_info(struct ecore_hwfn *p_hwfn,
					    struct ecore_cxt_info *p_info)
{
	struct ecore_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	struct ecore_cid_acquired_map *p_map = OSAL_NULL;
	u32 conn_cxt_size, hw_p_size, cxts_per_p, line;
	enum protocol_type type;
	bool b_acquired;

	/* Test acquired and find matching per-protocol map */
	b_acquired = ecore_cxt_test_cid_acquired(p_hwfn, p_info->iid,
						 ECORE_CXT_PF_CID,
						 &type, &p_map);

	if (!b_acquired)
		return ECORE_INVAL;

	/* set the protocl type */
	p_info->type = type;

	/* compute context virtual pointer */
	hw_p_size = p_hwfn->p_cxt_mngr->clients[ILT_CLI_CDUC].p_size.val;

	conn_cxt_size = CONN_CXT_SIZE(p_hwfn);
	cxts_per_p = ILT_PAGE_IN_BYTES(hw_p_size) / conn_cxt_size;
	line = p_info->iid / cxts_per_p;

	/* Make sure context is allocated (dynamic allocation) */
	if (!p_mngr->ilt_shadow[line].p_virt)
		return ECORE_INVAL;

	p_info->p_cxt = (u8 *)p_mngr->ilt_shadow[line].p_virt +
			      p_info->iid % cxts_per_p * conn_cxt_size;

	DP_VERBOSE(p_hwfn, (ECORE_MSG_ILT | ECORE_MSG_CXT),
		   "Accessing ILT shadow[%d]: CXT pointer is at %p (for iid %d)\n",
		   (p_info->iid / cxts_per_p), p_info->p_cxt, p_info->iid);

	return ECORE_SUCCESS;
}