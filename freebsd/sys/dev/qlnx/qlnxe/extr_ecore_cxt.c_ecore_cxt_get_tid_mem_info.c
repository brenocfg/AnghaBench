#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct ecore_tid_seg {size_t type; int /*<<< orphan*/  has_fl_mem; } ;
struct ecore_tid_mem {int tid_size; int num_tids_per_block; scalar_t__ waste; int /*<<< orphan*/ * blocks; } ;
struct TYPE_8__ {int /*<<< orphan*/  val; } ;
struct ecore_ilt_client_cfg {TYPE_4__ p_size; struct ecore_ilt_cli_blk* pf_blks; int /*<<< orphan*/  active; } ;
struct ecore_ilt_cli_blk {int real_size_in_page; size_t start_line; int /*<<< orphan*/  total_size; } ;
struct TYPE_5__ {int personality; } ;
struct ecore_hwfn {struct ecore_cxt_mngr* p_cxt_mngr; TYPE_1__ hw_info; } ;
struct ecore_cxt_mngr {size_t pf_start_line; int* task_type_size; TYPE_3__* ilt_shadow; TYPE_2__* conn_cfg; struct ecore_ilt_client_cfg* clients; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_7__ {int /*<<< orphan*/  p_virt; } ;
struct TYPE_6__ {struct ecore_tid_seg* tid_seg; } ;

/* Variables and functions */
 size_t CDUT_FL_SEG_BLK (size_t,int /*<<< orphan*/ ) ; 
 size_t DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 size_t ECORE_CXT_FCOE_TID_SEG ; 
 size_t ECORE_CXT_ISCSI_TID_SEG ; 
 int ECORE_INVAL ; 
#define  ECORE_PCI_FCOE 129 
#define  ECORE_PCI_ISCSI 128 
 int ECORE_SUCCESS ; 
 size_t ILT_CLI_CDUT ; 
 scalar_t__ ILT_PAGE_IN_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF ; 
 size_t PROTOCOLID_FCOE ; 
 size_t PROTOCOLID_ISCSI ; 

enum _ecore_status_t ecore_cxt_get_tid_mem_info(struct ecore_hwfn *p_hwfn,
						struct ecore_tid_mem *p_info)
{
	struct ecore_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	u32 proto, seg, total_lines, i, shadow_line;
	struct ecore_ilt_client_cfg *p_cli;
	struct ecore_ilt_cli_blk *p_fl_seg;
	struct ecore_tid_seg *p_seg_info;

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
	if (!p_seg_info->has_fl_mem)
		return ECORE_INVAL;

	p_fl_seg = &p_cli->pf_blks[CDUT_FL_SEG_BLK(seg, PF)];
	total_lines = DIV_ROUND_UP(p_fl_seg->total_size,
				   p_fl_seg->real_size_in_page);

	for (i = 0; i < total_lines; i++) {
		shadow_line = i + p_fl_seg->start_line -
			      p_hwfn->p_cxt_mngr->pf_start_line;
		p_info->blocks[i] = p_mngr->ilt_shadow[shadow_line].p_virt;
	}
	p_info->waste = ILT_PAGE_IN_BYTES(p_cli->p_size.val) -
			p_fl_seg->real_size_in_page;
	p_info->tid_size = p_mngr->task_type_size[p_seg_info->type];
	p_info->num_tids_per_block = p_fl_seg->real_size_in_page /
				     p_info->tid_size;

	return ECORE_SUCCESS;
}