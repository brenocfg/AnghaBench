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
typedef  int u32 ;
struct ecore_hwfn {struct ecore_cxt_mngr* p_cxt_mngr; } ;
struct ecore_cxt_mngr {TYPE_2__* clients; struct ecore_conn_type_cfg* conn_cfg; } ;
struct ecore_conn_type_cfg {int cid_count; void* cids_per_vf; } ;
typedef  enum protocol_type { ____Placeholder_protocol_type } protocol_type ;
struct TYPE_3__ {int val; } ;
struct TYPE_4__ {TYPE_1__ p_size; } ;

/* Variables and functions */
 int CONN_CXT_SIZE (struct ecore_hwfn*) ; 
 int DQ_RANGE_ALIGN ; 
 size_t ILT_CLI_CDUC ; 
 int ILT_PAGE_IN_BYTES (int) ; 
 int PROTOCOLID_ROCE ; 
 void* ROUNDUP (int,int) ; 

__attribute__((used)) static void ecore_cxt_set_proto_cid_count(struct ecore_hwfn *p_hwfn,
					  enum protocol_type type,
					  u32 cid_count, u32 vf_cid_cnt)
{
	struct ecore_cxt_mngr *p_mgr = p_hwfn->p_cxt_mngr;
	struct ecore_conn_type_cfg *p_conn = &p_mgr->conn_cfg[type];

	p_conn->cid_count = ROUNDUP(cid_count, DQ_RANGE_ALIGN);
	p_conn->cids_per_vf = ROUNDUP(vf_cid_cnt, DQ_RANGE_ALIGN);

	if (type == PROTOCOLID_ROCE) {
		u32 page_sz = p_mgr->clients[ILT_CLI_CDUC].p_size.val;
		u32 cxt_size = CONN_CXT_SIZE(p_hwfn);
		u32 elems_per_page = ILT_PAGE_IN_BYTES(page_sz) / cxt_size;
		u32 align = elems_per_page * DQ_RANGE_ALIGN;

		p_conn->cid_count = ROUNDUP(p_conn->cid_count, align);
	}
}