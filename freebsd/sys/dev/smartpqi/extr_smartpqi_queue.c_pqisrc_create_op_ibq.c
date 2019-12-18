#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_19__ {scalar_t__ pci_mem_base_vaddr; } ;
typedef  TYPE_5__ pqisrc_softstate_t ;
struct TYPE_20__ {int elem_size; scalar_t__ pi_register_offset; int /*<<< orphan*/ * pi_register_abs; int /*<<< orphan*/  num_elem; int /*<<< orphan*/  ci_dma_addr; int /*<<< orphan*/  array_dma_addr; int /*<<< orphan*/  q_id; } ;
typedef  TYPE_6__ ib_queue_t ;
struct TYPE_17__ {int /*<<< orphan*/ * status_desc; scalar_t__ pi_offset; } ;
struct TYPE_18__ {TYPE_3__ create_op_iq; } ;
struct TYPE_15__ {int elem_len; int /*<<< orphan*/  num_elem; int /*<<< orphan*/  iq_ci_addr; int /*<<< orphan*/  elem_arr_addr; int /*<<< orphan*/  qid; } ;
struct TYPE_16__ {TYPE_1__ create_op_iq; } ;
struct TYPE_21__ {TYPE_4__ resp_type; TYPE_2__ req_type; int /*<<< orphan*/  fn_code; } ;
typedef  TYPE_7__ gen_adm_resp_iu_t ;
typedef  TYPE_7__ gen_adm_req_iu_t ;
typedef  int /*<<< orphan*/  admin_resp ;
typedef  int /*<<< orphan*/  admin_req ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*,...) ; 
 int /*<<< orphan*/  DBG_WARN (char*,...) ; 
 scalar_t__ PQISRC_PQI_REG_OFFSET ; 
 int /*<<< orphan*/  PQI_FUNCTION_CREATE_OPERATIONAL_IQ ; 
 int PQI_STATUS_SUCCESS ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int pqisrc_submit_admin_req (TYPE_5__*,TYPE_7__*,TYPE_7__*) ; 

int pqisrc_create_op_ibq(pqisrc_softstate_t *softs,
			ib_queue_t *op_ib_q)
{
	int ret = PQI_STATUS_SUCCESS;;
	gen_adm_req_iu_t admin_req;
	gen_adm_resp_iu_t admin_resp;

	DBG_FUNC("IN\n");

	memset(&admin_req, 0, sizeof(admin_req));
	memset(&admin_resp, 0, sizeof(admin_resp));

	admin_req.fn_code = PQI_FUNCTION_CREATE_OPERATIONAL_IQ;
	admin_req.req_type.create_op_iq.qid = op_ib_q->q_id;
	admin_req.req_type.create_op_iq.elem_arr_addr = op_ib_q->array_dma_addr;
	admin_req.req_type.create_op_iq.iq_ci_addr = op_ib_q->ci_dma_addr;
	admin_req.req_type.create_op_iq.num_elem =  op_ib_q->num_elem;
	admin_req.req_type.create_op_iq.elem_len = op_ib_q->elem_size / 16;
	
	ret = pqisrc_submit_admin_req(softs, &admin_req, &admin_resp);
	
	if( PQI_STATUS_SUCCESS == ret) {
		op_ib_q->pi_register_offset =(PQISRC_PQI_REG_OFFSET + 
				admin_resp.resp_type.create_op_iq.pi_offset);
        
		op_ib_q->pi_register_abs =(uint32_t *)(softs->pci_mem_base_vaddr +
				op_ib_q->pi_register_offset);
	} else {
		int i = 0;
		DBG_WARN("Error Status Decsriptors\n");
		for(i = 0; i < 4;i++)
			DBG_WARN(" %x ",admin_resp.resp_type.create_op_iq.status_desc[i]);		
	}

	DBG_FUNC("OUT ret : %d\n", ret);
	return ret;		
}