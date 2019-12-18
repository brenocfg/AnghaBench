#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ flags1; } ;
struct TYPE_8__ {TYPE_2__ tdif_context; } ;
union type1_task_context {TYPE_3__ roce_ctx; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
typedef  size_t u32 ;
struct ecore_ptt {int dummy; } ;
struct TYPE_6__ {size_t val; } ;
struct ecore_ilt_client_cfg {TYPE_1__ p_size; struct ecore_ilt_cli_blk* pf_blks; } ;
struct ecore_ilt_cli_blk {size_t start_line; int /*<<< orphan*/  real_size_in_page; } ;
struct ecore_hwfn {int b_rdma_enabled_in_prs; TYPE_5__* p_cxt_mngr; int /*<<< orphan*/  rdma_prs_search_reg; int /*<<< orphan*/  p_dev; } ;
typedef  scalar_t__ osal_uintptr_t ;
typedef  int /*<<< orphan*/  ilt_hw_entry ;
typedef  enum ecore_cxt_elem_type { ____Placeholder_ecore_cxt_elem_type } ecore_cxt_elem_type ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
typedef  int dma_addr_t ;
struct TYPE_10__ {size_t pf_start_line; int /*<<< orphan*/  mutex; TYPE_4__* ilt_shadow; struct ecore_ilt_client_cfg* clients; } ;
struct TYPE_9__ {int p_phys; int /*<<< orphan*/  size; void* p_virt; } ;

/* Variables and functions */
 size_t CDUC_BLK ; 
 size_t CDUT_SEG_BLK (int /*<<< orphan*/ ) ; 
 size_t CONN_CXT_SIZE (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,...) ; 
 int /*<<< orphan*/  ECORE_CXT_ROCE_TID_SEG ; 
#define  ECORE_ELEM_CXT 131 
#define  ECORE_ELEM_SRQ 130 
#define  ECORE_ELEM_TASK 129 
#define  ECORE_ELEM_XRC_SRQ 128 
 int ECORE_INVAL ; 
 int ECORE_NOMEM ; 
 int ECORE_SUCCESS ; 
 int ECORE_TIMEOUT ; 
 size_t ILT_CLI_CDUC ; 
 size_t ILT_CLI_CDUT ; 
 size_t ILT_CLI_TSDM ; 
 size_t ILT_ENTRY_IN_REGS ; 
 int /*<<< orphan*/  ILT_ENTRY_PHY_ADDR ; 
 int /*<<< orphan*/  ILT_ENTRY_VALID ; 
 size_t ILT_PAGE_IN_BYTES (size_t) ; 
 size_t ILT_REG_SIZE_IN_BYTES ; 
 void* OSAL_DMA_ALLOC_COHERENT (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_MEM_ZERO (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_MUTEX_ACQUIRE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_MUTEX_RELEASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_NULL ; 
 int /*<<< orphan*/  PRS_REG_ROCE_DEST_QP_MAX_PF ; 
 size_t PSWRQ2_REG_ILT_MEMORY ; 
 int /*<<< orphan*/  SET_FIELD (scalar_t__,int /*<<< orphan*/ ,int) ; 
 size_t SRQ_BLK ; 
 size_t SRQ_CXT_SIZE ; 
 int /*<<< orphan*/  TDIF_TASK_CONTEXT_REF_TAG_MASK ; 
 size_t TYPE1_TASK_CXT_SIZE (struct ecore_hwfn*) ; 
 size_t XRC_SRQ_CXT_SIZE ; 
 size_t ecore_cxt_srqs_per_page (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_dmae_host2grc (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__,size_t,int,int /*<<< orphan*/ ) ; 
 struct ecore_ptt* ecore_ptt_acquire (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_ptt_release (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

enum _ecore_status_t
ecore_cxt_dynamic_ilt_alloc(struct ecore_hwfn *p_hwfn,
			    enum ecore_cxt_elem_type elem_type,
			    u32 iid)
{
	u32 reg_offset, shadow_line, elem_size, hw_p_size, elems_per_p, line;
	struct ecore_ilt_client_cfg *p_cli;
	struct ecore_ilt_cli_blk *p_blk;
	struct ecore_ptt *p_ptt;
	dma_addr_t p_phys;
	u64 ilt_hw_entry;
	void *p_virt;
	enum _ecore_status_t rc = ECORE_SUCCESS;

	switch (elem_type) {
	case ECORE_ELEM_CXT:
		p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_CDUC];
		elem_size = CONN_CXT_SIZE(p_hwfn);
		p_blk = &p_cli->pf_blks[CDUC_BLK];
		break;
	case ECORE_ELEM_SRQ:
		/* The first ILT page is not used for regular SRQs. Skip it. */
		iid += ecore_cxt_srqs_per_page(p_hwfn);
		p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_TSDM];
		elem_size = SRQ_CXT_SIZE;
		p_blk = &p_cli->pf_blks[SRQ_BLK];
		break;
	case ECORE_ELEM_XRC_SRQ:
		p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_TSDM];
		elem_size = XRC_SRQ_CXT_SIZE;
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
	line = p_blk->start_line + (iid / elems_per_p);
	shadow_line = line - p_hwfn->p_cxt_mngr->pf_start_line;

	/* If line is already allocated, do nothing, otherwise allocate it and
	 * write it to the PSWRQ2 registers.
	 * This section can be run in parallel from different contexts and thus
	 * a mutex protection is needed.
	 */
#ifdef _NTDDK_
#pragma warning(suppress : 28121)
#endif
	OSAL_MUTEX_ACQUIRE(&p_hwfn->p_cxt_mngr->mutex);

	if (p_hwfn->p_cxt_mngr->ilt_shadow[shadow_line].p_virt)
		goto out0;

	p_ptt = ecore_ptt_acquire(p_hwfn);
	if (!p_ptt) {
		DP_NOTICE(p_hwfn, false,
			  "ECORE_TIME_OUT on ptt acquire - dynamic allocation");
		rc = ECORE_TIMEOUT;
		goto out0;
	}

	p_virt = OSAL_DMA_ALLOC_COHERENT(p_hwfn->p_dev,
					 &p_phys,
					 p_blk->real_size_in_page);
	if (!p_virt) {
		rc = ECORE_NOMEM;
		goto out1;
	}
	OSAL_MEM_ZERO(p_virt, p_blk->real_size_in_page);

	/* configuration of refTagMask to 0xF is required for RoCE DIF MR only,
	 * to compensate for a HW bug, but it is configured even if DIF is not
	 * enabled. This is harmless and allows us to avoid a dedicated API. We
	 * configure the field for all of the contexts on the newly allocated
	 * page.
	 */
	if (elem_type == ECORE_ELEM_TASK) {
		u32 elem_i;
		u8 *elem_start = (u8 *)p_virt;
		union type1_task_context *elem;

		for (elem_i = 0; elem_i < elems_per_p; elem_i++) {
			elem = (union type1_task_context *)elem_start;
			SET_FIELD(elem->roce_ctx.tdif_context.flags1,
				  TDIF_TASK_CONTEXT_REF_TAG_MASK , 0xf);
			elem_start += TYPE1_TASK_CXT_SIZE(p_hwfn);
		}
	}

	p_hwfn->p_cxt_mngr->ilt_shadow[shadow_line].p_virt = p_virt;
	p_hwfn->p_cxt_mngr->ilt_shadow[shadow_line].p_phys = p_phys;
	p_hwfn->p_cxt_mngr->ilt_shadow[shadow_line].size =
		p_blk->real_size_in_page;

	/* compute absolute offset */
	reg_offset = PSWRQ2_REG_ILT_MEMORY +
		     (line * ILT_REG_SIZE_IN_BYTES * ILT_ENTRY_IN_REGS);

	ilt_hw_entry = 0;
	SET_FIELD(ilt_hw_entry, ILT_ENTRY_VALID, 1ULL);
	SET_FIELD(ilt_hw_entry,
		  ILT_ENTRY_PHY_ADDR,
		  (p_hwfn->p_cxt_mngr->ilt_shadow[shadow_line].p_phys >> 12));

	/* Write via DMAE since the PSWRQ2_REG_ILT_MEMORY line is a wide-bus */
	ecore_dmae_host2grc(p_hwfn, p_ptt, (u64)(osal_uintptr_t)&ilt_hw_entry,
			    reg_offset, sizeof(ilt_hw_entry) / sizeof(u32),
			    OSAL_NULL /* default parameters */);

	if (elem_type == ECORE_ELEM_CXT) {
		u32 last_cid_allocated = (1 + (iid / elems_per_p)) *
					 elems_per_p;

		/* Update the relevant register in the parser */
		ecore_wr(p_hwfn, p_ptt, PRS_REG_ROCE_DEST_QP_MAX_PF,
			 last_cid_allocated - 1);

		/* RoCE w/a -> we don't write to the prs search reg until first
		 * cid is allocated. This is because the prs checks
		 * last_cid-1 >=0 making 0 a valid value... this will cause
		 * the a context load to occur on a RoCE packet received with
		 * cid=0 even before context was initialized, can happen with a
		 * stray packet from switch or a packet with crc-error
		 */

		if (!p_hwfn->b_rdma_enabled_in_prs) {
			/* Enable Rdma search */
			ecore_wr(p_hwfn, p_ptt, p_hwfn->rdma_prs_search_reg, 1);
			p_hwfn->b_rdma_enabled_in_prs = true;
		}
	}

out1:
	ecore_ptt_release(p_hwfn, p_ptt);
out0:
	OSAL_MUTEX_RELEASE(&p_hwfn->p_cxt_mngr->mutex);

	return rc;
}