#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct dma_mem {int dummy; } ;
struct TYPE_27__ {int /*<<< orphan*/  intr_coales_time_granularity; int /*<<< orphan*/  max_oq_elem_len; int /*<<< orphan*/  max_oq_elements; int /*<<< orphan*/  max_oqs; int /*<<< orphan*/  min_iq_elem_len; int /*<<< orphan*/  max_iq_elem_len; int /*<<< orphan*/  max_iq_elements; int /*<<< orphan*/  max_iqs; } ;
struct TYPE_28__ {int /*<<< orphan*/  ob_spanning_supported; int /*<<< orphan*/  ib_spanning_supported; int /*<<< orphan*/  max_ib_iu_length_per_fw; TYPE_4__ pqi_dev_cap; } ;
typedef  TYPE_5__ pqisrc_softstate_t ;
struct TYPE_29__ {int /*<<< orphan*/  ob_spanning_supported; int /*<<< orphan*/  ib_spanning_supported; int /*<<< orphan*/  max_ib_iu_len; } ;
typedef  TYPE_6__ pqi_iu_layer_desc_t ;
struct TYPE_30__ {TYPE_6__* iu_layer_desc; int /*<<< orphan*/  intr_coales_time_granularity; int /*<<< orphan*/  max_oq_elem_len; int /*<<< orphan*/  max_oq_elements; int /*<<< orphan*/  max_oqs; int /*<<< orphan*/  min_iq_elem_len; int /*<<< orphan*/  max_iq_elem_len; int /*<<< orphan*/  max_iq_elements; int /*<<< orphan*/  max_iqs; } ;
typedef  TYPE_7__ pqi_dev_cap_t ;
struct TYPE_24__ {int /*<<< orphan*/  type; int /*<<< orphan*/  addr; int /*<<< orphan*/  length; } ;
struct TYPE_25__ {TYPE_1__ sg_desc; int /*<<< orphan*/  buf_size; } ;
struct TYPE_26__ {TYPE_2__ general_func; } ;
struct TYPE_31__ {char* tag; int /*<<< orphan*/  size; int /*<<< orphan*/  virt_addr; TYPE_3__ req_type; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  fn_code; int /*<<< orphan*/  align; } ;
typedef  TYPE_8__ gen_adm_resp_iu_t ;
typedef  TYPE_8__ gen_adm_req_iu_t ;
typedef  TYPE_8__ dma_mem_t ;
typedef  int /*<<< orphan*/  admin_resp ;
typedef  int /*<<< orphan*/  admin_req ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ERR (char*,...) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  DBG_INIT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQISRC_DEFAULT_DMA_ALIGN ; 
 int /*<<< orphan*/  PQI_FUNCTION_REPORT_DEV_CAP ; 
 size_t PQI_PROTOCOL_SOP ; 
 int PQI_STATUS_FAILURE ; 
 int PQI_STATUS_SUCCESS ; 
 int /*<<< orphan*/  REPORT_PQI_DEV_CAP_DATA_BUF_SIZE ; 
 int /*<<< orphan*/  SGL_DESCRIPTOR_CODE_DATA_BLOCK ; 
 int /*<<< orphan*/  memcpy (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 int os_dma_mem_alloc (TYPE_5__*,TYPE_8__*) ; 
 int /*<<< orphan*/  os_dma_mem_free (TYPE_5__*,TYPE_8__*) ; 
 TYPE_7__* os_mem_alloc (TYPE_5__*,int) ; 
 int /*<<< orphan*/  os_mem_free (TYPE_5__*,void*,int /*<<< orphan*/ ) ; 
 int pqisrc_submit_admin_req (TYPE_5__*,TYPE_8__*,TYPE_8__*) ; 

__attribute__((used)) static int pqisrc_report_pqi_capability(pqisrc_softstate_t *softs)
{
	int ret = PQI_STATUS_SUCCESS;
	
	DBG_FUNC("IN\n");

	gen_adm_req_iu_t	admin_req;
	gen_adm_resp_iu_t 	admin_resp;
	dma_mem_t		pqi_cap_dma_buf;
	pqi_dev_cap_t 		*capability = NULL;
	pqi_iu_layer_desc_t	*iu_layer_desc = NULL;

	/* Allocate Non DMA memory */
	capability = os_mem_alloc(softs, sizeof(*capability));
	if (!capability) {
		DBG_ERR("Failed to allocate memory for capability\n");
		ret = PQI_STATUS_FAILURE;
		goto err_out;
	}

	memset(&admin_req, 0, sizeof(admin_req));
	memset(&admin_resp, 0, sizeof(admin_resp));

	memset(&pqi_cap_dma_buf, 0, sizeof(struct dma_mem));
	pqi_cap_dma_buf.tag = "pqi_cap_buf";
	pqi_cap_dma_buf.size = REPORT_PQI_DEV_CAP_DATA_BUF_SIZE;
	pqi_cap_dma_buf.align = PQISRC_DEFAULT_DMA_ALIGN;

	ret = os_dma_mem_alloc(softs, &pqi_cap_dma_buf);
	if (ret) {
		DBG_ERR("Failed to allocate capability DMA buffer : %d\n", ret);
		goto err_dma_alloc;
	}
	
	admin_req.fn_code = PQI_FUNCTION_REPORT_DEV_CAP;
	admin_req.req_type.general_func.buf_size = pqi_cap_dma_buf.size;
	admin_req.req_type.general_func.sg_desc.length = pqi_cap_dma_buf.size;
	admin_req.req_type.general_func.sg_desc.addr = pqi_cap_dma_buf.dma_addr;
	admin_req.req_type.general_func.sg_desc.type =	SGL_DESCRIPTOR_CODE_DATA_BLOCK;

	ret = pqisrc_submit_admin_req(softs, &admin_req, &admin_resp);
	if( PQI_STATUS_SUCCESS == ret) {
                memcpy(capability,
			pqi_cap_dma_buf.virt_addr,
			pqi_cap_dma_buf.size);
	} else {
		DBG_ERR("Failed to send admin req report pqi device capability\n");
		goto err_admin_req;
		
	}

	softs->pqi_dev_cap.max_iqs = capability->max_iqs;
	softs->pqi_dev_cap.max_iq_elements = capability->max_iq_elements;
	softs->pqi_dev_cap.max_iq_elem_len = capability->max_iq_elem_len;
	softs->pqi_dev_cap.min_iq_elem_len = capability->min_iq_elem_len;
	softs->pqi_dev_cap.max_oqs = capability->max_oqs;
	softs->pqi_dev_cap.max_oq_elements = capability->max_oq_elements;
	softs->pqi_dev_cap.max_oq_elem_len = capability->max_oq_elem_len;
	softs->pqi_dev_cap.intr_coales_time_granularity = capability->intr_coales_time_granularity;

	iu_layer_desc = &capability->iu_layer_desc[PQI_PROTOCOL_SOP];
	softs->max_ib_iu_length_per_fw = iu_layer_desc->max_ib_iu_len;
	softs->ib_spanning_supported = iu_layer_desc->ib_spanning_supported;
	softs->ob_spanning_supported = iu_layer_desc->ob_spanning_supported;

	DBG_INIT("softs->pqi_dev_cap.max_iqs: %d\n", softs->pqi_dev_cap.max_iqs);
	DBG_INIT("softs->pqi_dev_cap.max_iq_elements: %d\n", softs->pqi_dev_cap.max_iq_elements);
	DBG_INIT("softs->pqi_dev_cap.max_iq_elem_len: %d\n", softs->pqi_dev_cap.max_iq_elem_len);
	DBG_INIT("softs->pqi_dev_cap.min_iq_elem_len: %d\n", softs->pqi_dev_cap.min_iq_elem_len);
	DBG_INIT("softs->pqi_dev_cap.max_oqs: %d\n", softs->pqi_dev_cap.max_oqs);
	DBG_INIT("softs->pqi_dev_cap.max_oq_elements: %d\n", softs->pqi_dev_cap.max_oq_elements);
	DBG_INIT("softs->pqi_dev_cap.max_oq_elem_len: %d\n", softs->pqi_dev_cap.max_oq_elem_len);
	DBG_INIT("softs->pqi_dev_cap.intr_coales_time_granularity: %d\n", softs->pqi_dev_cap.intr_coales_time_granularity);
	DBG_INIT("softs->max_ib_iu_length_per_fw: %d\n", softs->max_ib_iu_length_per_fw);
	DBG_INIT("softs->ib_spanning_supported: %d\n", softs->ib_spanning_supported);
	DBG_INIT("softs->ob_spanning_supported: %d\n", softs->ob_spanning_supported);
	

	os_mem_free(softs, (void *)capability,
		    REPORT_PQI_DEV_CAP_DATA_BUF_SIZE);
	os_dma_mem_free(softs, &pqi_cap_dma_buf);

	DBG_FUNC("OUT\n");
	return ret;

err_admin_req:
	os_dma_mem_free(softs, &pqi_cap_dma_buf);
err_dma_alloc:
	if (capability)
		os_mem_free(softs, (void *)capability,
			    REPORT_PQI_DEV_CAP_DATA_BUF_SIZE);
err_out:
	DBG_FUNC("failed OUT\n");
	return PQI_STATUS_FAILURE;
}