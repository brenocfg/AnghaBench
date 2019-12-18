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
typedef  scalar_t__ u8 ;
struct TYPE_10__ {void* lo; void* hi; } ;
struct TYPE_9__ {void* lo; void* hi; } ;
struct rdma_resize_cq_ramrod_data {TYPE_5__ output_params_addr; TYPE_4__ pbl_addr; int /*<<< orphan*/  max_cqes; int /*<<< orphan*/  pbl_num_pages; scalar_t__ pbl_log_page_size; scalar_t__ flags; } ;
struct rdma_resize_cq_output_params {int /*<<< orphan*/  old_cq_cons; int /*<<< orphan*/  old_cq_prod; } ;
struct TYPE_8__ {struct rdma_resize_cq_ramrod_data rdma_resize_cq; } ;
struct ecore_spq_entry {TYPE_3__ ramrod; } ;
struct ecore_sp_init_data {int cid; int /*<<< orphan*/  comp_mode; int /*<<< orphan*/  opaque_fid; } ;
struct ecore_rdma_resize_cq_out_params {void* cons; void* prod; } ;
struct ecore_rdma_resize_cq_in_params {int icid; int pbl_two_level; int /*<<< orphan*/  pbl_ptr; int /*<<< orphan*/  cq_size; int /*<<< orphan*/  pbl_num_pages; scalar_t__ pbl_page_size_log; } ;
struct TYPE_6__ {int /*<<< orphan*/  opaque_fid; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; TYPE_2__* p_rdma_info; TYPE_1__ hw_info; } ;
typedef  int /*<<< orphan*/  init_data ;
typedef  enum ecore_rdma_toggle_bit { ____Placeholder_ecore_rdma_toggle_bit } ecore_rdma_toggle_bit ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_7__ {int /*<<< orphan*/  proto; } ;

/* Variables and functions */
 void* DMA_HI_LE (int /*<<< orphan*/ ) ; 
 void* DMA_LO_LE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 int ECORE_NOMEM ; 
 int /*<<< orphan*/  ECORE_SPQ_MODE_EBLOCK ; 
 int ECORE_SUCCESS ; 
 int ECORE_UNKNOWN_ERROR ; 
 int /*<<< orphan*/  OSAL_CPU_TO_LE16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_CPU_TO_LE32 (int /*<<< orphan*/ ) ; 
 scalar_t__ OSAL_DMA_ALLOC_COHERENT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OSAL_DMA_FREE_COHERENT (int /*<<< orphan*/ ,struct rdma_resize_cq_output_params*,int /*<<< orphan*/ ,int) ; 
 void* OSAL_LE32_TO_CPU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RDMA_RAMROD_RESIZE_CQ ; 
 int /*<<< orphan*/  RDMA_RESIZE_CQ_RAMROD_DATA_IS_TWO_LEVEL_PBL ; 
 int /*<<< orphan*/  RDMA_RESIZE_CQ_RAMROD_DATA_TOGGLE_BIT ; 
 scalar_t__ RDMA_RETURN_OK ; 
 scalar_t__ RDMA_RETURN_RESIZE_CQ_ERR ; 
 int /*<<< orphan*/  SET_FIELD (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int ecore_rdma_toggle_bit_create_resize_cq (struct ecore_hwfn*,int) ; 
 int ecore_sp_init_request (struct ecore_hwfn*,struct ecore_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ecore_sp_init_data*) ; 
 int ecore_spq_post (struct ecore_hwfn*,struct ecore_spq_entry*,scalar_t__*) ; 

enum _ecore_status_t ecore_rdma_resize_cq(void			*rdma_cxt,
			struct ecore_rdma_resize_cq_in_params	*in_params,
			struct ecore_rdma_resize_cq_out_params	*out_params)
{
	enum _ecore_status_t			rc;
	enum ecore_rdma_toggle_bit		toggle_bit;
	struct ecore_spq_entry			*p_ent;
	struct rdma_resize_cq_ramrod_data	*p_ramrod;
	u8                                      fw_return_code;
	struct ecore_hwfn *p_hwfn = (struct ecore_hwfn *)rdma_cxt;
	dma_addr_t							ramrod_res_phys;
	struct rdma_resize_cq_output_params	*p_ramrod_res;
	struct ecore_sp_init_data		init_data;

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "icid = %08x\n", in_params->icid);

	/* Send resize CQ ramrod */

	p_ramrod_res = (struct rdma_resize_cq_output_params *)
			OSAL_DMA_ALLOC_COHERENT(p_hwfn->p_dev, &ramrod_res_phys,
				sizeof(*p_ramrod_res));
	if (!p_ramrod_res)
	{
		rc = ECORE_NOMEM;
		DP_NOTICE(p_hwfn, false,
			  "ecore resize cq failed: cannot allocate memory (ramrod). rc = %d\n",
			  rc);
		return rc;
	}

	/* Get SPQ entry */
	OSAL_MEMSET(&init_data, 0, sizeof(init_data));
	init_data.cid = in_params->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = ECORE_SPQ_MODE_EBLOCK;

	rc = ecore_sp_init_request(p_hwfn, &p_ent,
				   RDMA_RAMROD_RESIZE_CQ,
				   p_hwfn->p_rdma_info->proto, &init_data);
	if (rc != ECORE_SUCCESS)
		goto err;

	p_ramrod = &p_ent->ramrod.rdma_resize_cq;

	p_ramrod->flags = 0;

	/* toggle the bit for every resize or create cq for a given icid */
	toggle_bit = ecore_rdma_toggle_bit_create_resize_cq(p_hwfn,
							    in_params->icid);

	SET_FIELD(p_ramrod->flags,
		  RDMA_RESIZE_CQ_RAMROD_DATA_TOGGLE_BIT,
		  toggle_bit);

	SET_FIELD(p_ramrod->flags,
		  RDMA_RESIZE_CQ_RAMROD_DATA_IS_TWO_LEVEL_PBL,
		  in_params->pbl_two_level);

	p_ramrod->pbl_log_page_size = in_params->pbl_page_size_log - 12;
	p_ramrod->pbl_num_pages = OSAL_CPU_TO_LE16(in_params->pbl_num_pages);
	p_ramrod->max_cqes = OSAL_CPU_TO_LE32(in_params->cq_size);
	p_ramrod->pbl_addr.hi = DMA_HI_LE(in_params->pbl_ptr);
	p_ramrod->pbl_addr.lo = DMA_LO_LE(in_params->pbl_ptr);

	p_ramrod->output_params_addr.hi = DMA_HI_LE(ramrod_res_phys);
	p_ramrod->output_params_addr.lo = DMA_LO_LE(ramrod_res_phys);

	rc = ecore_spq_post(p_hwfn, p_ent, &fw_return_code);
	if (rc != ECORE_SUCCESS)
		goto err;

	if (fw_return_code != RDMA_RETURN_OK)
	{
		DP_NOTICE(p_hwfn, fw_return_code != RDMA_RETURN_RESIZE_CQ_ERR,
			  "fw_return_code = %d\n", fw_return_code);
		DP_NOTICE(p_hwfn,
			  true, "fw_return_code = %d\n", fw_return_code);
		rc = ECORE_UNKNOWN_ERROR;
		goto err;
	}

	out_params->prod = OSAL_LE32_TO_CPU(p_ramrod_res->old_cq_prod);
	out_params->cons = OSAL_LE32_TO_CPU(p_ramrod_res->old_cq_cons);

	OSAL_DMA_FREE_COHERENT(p_hwfn->p_dev, p_ramrod_res, ramrod_res_phys,
			       sizeof(*p_ramrod_res));

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "rc = %d\n", rc);

	return rc;

err:
	OSAL_DMA_FREE_COHERENT(p_hwfn->p_dev, p_ramrod_res, ramrod_res_phys,
			       sizeof(*p_ramrod_res));
	DP_NOTICE(p_hwfn, false, "rc = %d\n", rc);

	return rc;
}