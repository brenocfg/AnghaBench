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
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
struct ecore_tid_seg {size_t type; int /*<<< orphan*/  has_fl_mem; } ;
struct ecore_ilt_client_cfg {struct ecore_ilt_cli_blk* pf_blks; int /*<<< orphan*/  active; } ;
struct ecore_ilt_cli_blk {size_t real_size_in_page; size_t start_line; int /*<<< orphan*/  total_size; } ;
struct TYPE_4__ {int personality; } ;
struct ecore_hwfn {TYPE_1__ hw_info; struct ecore_cxt_mngr* p_cxt_mngr; } ;
struct ecore_cxt_mngr {size_t* task_type_size; size_t pf_start_line; TYPE_3__* ilt_shadow; TYPE_2__* conn_cfg; struct ecore_ilt_client_cfg* clients; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_6__ {scalar_t__ p_virt; } ;
struct TYPE_5__ {struct ecore_tid_seg* tid_seg; } ;

/* Variables and functions */
 size_t CDUT_FL_SEG_BLK (size_t,int /*<<< orphan*/ ) ; 
 size_t CDUT_SEG_BLK (size_t) ; 
 size_t DIV_ROUND_UP (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ ECORE_CTX_FL_MEM ; 
 scalar_t__ ECORE_CTX_WORKING_MEM ; 
 size_t ECORE_CXT_FCOE_TID_SEG ; 
 size_t ECORE_CXT_ISCSI_TID_SEG ; 
 int ECORE_INVAL ; 
#define  ECORE_PCI_FCOE 129 
#define  ECORE_PCI_ISCSI 128 
 int ECORE_SUCCESS ; 
 size_t ILT_CLI_CDUT ; 
 int /*<<< orphan*/  PF ; 
 size_t PROTOCOLID_FCOE ; 
 size_t PROTOCOLID_ISCSI ; 

enum _ecore_status_t ecore_cxt_get_task_ctx(struct ecore_hwfn *p_hwfn,
					    u32 tid,
					    u8 ctx_type,
					    void **pp_task_ctx)
{
	struct ecore_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	struct ecore_ilt_client_cfg *p_cli;
	struct ecore_tid_seg *p_seg_info;
	struct ecore_ilt_cli_blk *p_seg;
	u32 num_tids_per_block;
	u32 tid_size, ilt_idx;
	u32 total_lines;
	u32 proto, seg;

	/* Verify the personality */
	switch (p_hwfn->hw_info.personality) {
	case ECORE_PCI_FCOE:
		proto = PROTOCOLID_FCOE;
		seg = ECORE_CXT_FCOE_TID_SEG;
		break;
	case ECORE_PCI_ISCSI:
		proto = PROTOCOLID_ISCSI;
		seg = ECORE_CXT_ISCSI_TID_SEG;
		break;
	default:
		return ECORE_INVAL;
	}

	p_cli = &p_mngr->clients[ILT_CLI_CDUT];
	if (!p_cli->active) {
		return ECORE_INVAL;
	}

	p_seg_info = &p_mngr->conn_cfg[proto].tid_seg[seg];

	if (ctx_type == ECORE_CTX_WORKING_MEM) {
		p_seg = &p_cli->pf_blks[CDUT_SEG_BLK(seg)];
	} else if (ctx_type == ECORE_CTX_FL_MEM) {
		if (!p_seg_info->has_fl_mem) {
			return ECORE_INVAL;
		}
		p_seg = &p_cli->pf_blks[CDUT_FL_SEG_BLK(seg, PF)];
	} else {
		return ECORE_INVAL;
	}
	total_lines = DIV_ROUND_UP(p_seg->total_size,
				   p_seg->real_size_in_page);
	tid_size = p_mngr->task_type_size[p_seg_info->type];
	num_tids_per_block = p_seg->real_size_in_page / tid_size;

	if (total_lines < tid/num_tids_per_block)
		return ECORE_INVAL;

	ilt_idx = tid / num_tids_per_block + p_seg->start_line -
		  p_mngr->pf_start_line;
	*pp_task_ctx = (u8 *)p_mngr->ilt_shadow[ilt_idx].p_virt +
			     (tid % num_tids_per_block) * tid_size;

	return ECORE_SUCCESS;
}