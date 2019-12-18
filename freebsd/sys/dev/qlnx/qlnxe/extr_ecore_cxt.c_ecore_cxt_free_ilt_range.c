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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct ecore_ptt {int dummy; } ;
struct TYPE_4__ {int val; } ;
struct ecore_ilt_client_cfg {TYPE_1__ p_size; struct ecore_ilt_cli_blk* pf_blks; } ;
struct ecore_ilt_cli_blk {int start_line; } ;
struct ecore_hwfn {TYPE_3__* p_cxt_mngr; int /*<<< orphan*/  p_dev; } ;
typedef  scalar_t__ osal_uintptr_t ;
typedef  int /*<<< orphan*/  ilt_hw_entry ;
typedef  enum ecore_cxt_elem_type { ____Placeholder_ecore_cxt_elem_type } ecore_cxt_elem_type ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_6__ {int pf_start_line; TYPE_2__* ilt_shadow; struct ecore_ilt_client_cfg* clients; } ;
struct TYPE_5__ {scalar_t__ size; scalar_t__ p_phys; scalar_t__ p_virt; } ;

/* Variables and functions */
 size_t CDUC_BLK ; 
 size_t CDUT_SEG_BLK (int /*<<< orphan*/ ) ; 
 int CONN_CXT_SIZE (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,...) ; 
 int /*<<< orphan*/  ECORE_CXT_ROCE_TID_SEG ; 
#define  ECORE_ELEM_CXT 130 
#define  ECORE_ELEM_SRQ 129 
#define  ECORE_ELEM_TASK 128 
 int ECORE_INVAL ; 
 int ECORE_SUCCESS ; 
 int ECORE_TIMEOUT ; 
 size_t ILT_CLI_CDUC ; 
 size_t ILT_CLI_CDUT ; 
 size_t ILT_CLI_TSDM ; 
 int ILT_ENTRY_IN_REGS ; 
 int ILT_PAGE_IN_BYTES (int) ; 
 int ILT_REG_SIZE_IN_BYTES ; 
 int /*<<< orphan*/  OSAL_DMA_FREE_COHERENT (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ OSAL_NULL ; 
 int PSWRQ2_REG_ILT_MEMORY ; 
 size_t SRQ_BLK ; 
 int SRQ_CXT_SIZE ; 
 int TYPE1_TASK_CXT_SIZE (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_dmae_host2grc (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__,int,int,scalar_t__) ; 
 struct ecore_ptt* ecore_ptt_acquire (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_ptt_release (struct ecore_hwfn*,struct ecore_ptt*) ; 

enum _ecore_status_t
ecore_cxt_free_ilt_range(struct ecore_hwfn *p_hwfn,
			 enum ecore_cxt_elem_type elem_type,
			 u32 start_iid, u32 count)
{
	u32 start_line, end_line, shadow_start_line, shadow_end_line;
	u32 reg_offset, elem_size, hw_p_size, elems_per_p;
	struct ecore_ilt_client_cfg *p_cli;
	struct ecore_ilt_cli_blk *p_blk;
	u32 end_iid = start_iid + count;
	struct ecore_ptt *p_ptt;
	u64 ilt_hw_entry = 0;
	u32 i;

	switch (elem_type) {
	case ECORE_ELEM_CXT:
		p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_CDUC];
		elem_size = CONN_CXT_SIZE(p_hwfn);
		p_blk = &p_cli->pf_blks[CDUC_BLK];
		break;
	case ECORE_ELEM_SRQ:
		p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_TSDM];
		elem_size = SRQ_CXT_SIZE;
		p_blk = &p_cli->pf_blks[SRQ_BLK];
		break;
	case ECORE_ELEM_TASK:
		p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_CDUT];
		elem_size = TYPE1_TASK_CXT_SIZE(p_hwfn);
		p_blk = &p_cli->pf_blks[CDUT_SEG_BLK(ECORE_CXT_ROCE_TID_SEG)];
		break;
	default:
		DP_NOTICE(p_hwfn, false,
			  "ECORE_INVALID elem type = %d", elem_type);
		return ECORE_INVAL;
	}

	/* Calculate line in ilt */
	hw_p_size = p_cli->p_size.val;
	elems_per_p = ILT_PAGE_IN_BYTES(hw_p_size) / elem_size;
	start_line = p_blk->start_line + (start_iid / elems_per_p);
	end_line = p_blk->start_line + (end_iid / elems_per_p);
	if (((end_iid + 1) / elems_per_p) != (end_iid / elems_per_p))
		end_line--;

	shadow_start_line = start_line - p_hwfn->p_cxt_mngr->pf_start_line;
	shadow_end_line = end_line - p_hwfn->p_cxt_mngr->pf_start_line;

	p_ptt = ecore_ptt_acquire(p_hwfn);
	if (!p_ptt) {
		DP_NOTICE(p_hwfn, false, "ECORE_TIME_OUT on ptt acquire - dynamic allocation");
		return ECORE_TIMEOUT;
	}

	for (i = shadow_start_line; i < shadow_end_line; i++) {
		if (!p_hwfn->p_cxt_mngr->ilt_shadow[i].p_virt)
			continue;

		OSAL_DMA_FREE_COHERENT(p_hwfn->p_dev,
				       p_hwfn->p_cxt_mngr->ilt_shadow[i].p_virt,
				       p_hwfn->p_cxt_mngr->ilt_shadow[i].p_phys,
				       p_hwfn->p_cxt_mngr->ilt_shadow[i].size);

		p_hwfn->p_cxt_mngr->ilt_shadow[i].p_virt = OSAL_NULL;
		p_hwfn->p_cxt_mngr->ilt_shadow[i].p_phys = 0;
		p_hwfn->p_cxt_mngr->ilt_shadow[i].size = 0;

		/* compute absolute offset */
		reg_offset = PSWRQ2_REG_ILT_MEMORY +
			     ((start_line++) * ILT_REG_SIZE_IN_BYTES *
			      ILT_ENTRY_IN_REGS);

		/* Write via DMAE since the PSWRQ2_REG_ILT_MEMORY line is a
		 * wide-bus.
		 */
		ecore_dmae_host2grc(p_hwfn, p_ptt,
				    (u64)(osal_uintptr_t)&ilt_hw_entry,
				    reg_offset,
				    sizeof(ilt_hw_entry) / sizeof(u32),
				    OSAL_NULL /* default parameters */);
	}

	ecore_ptt_release(p_hwfn, p_ptt);

	return ECORE_SUCCESS;
}