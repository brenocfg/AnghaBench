#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  pqisrc_softstate_t ;
struct TYPE_12__ {int /*<<< orphan*/  q_id; } ;
typedef  TYPE_3__ ib_queue_t ;
struct TYPE_10__ {int /*<<< orphan*/  vend_specific; int /*<<< orphan*/  qid; } ;
struct TYPE_11__ {TYPE_1__ change_op_iq_prop; } ;
struct TYPE_13__ {TYPE_2__ req_type; int /*<<< orphan*/  fn_code; } ;
typedef  TYPE_4__ gen_adm_resp_iu_t ;
typedef  TYPE_4__ gen_adm_req_iu_t ;
typedef  int /*<<< orphan*/  admin_resp ;
typedef  int /*<<< orphan*/  admin_req ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  PQI_FUNCTION_CHANGE_OPERATIONAL_IQ_PROP ; 
 int PQI_STATUS_SUCCESS ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int pqisrc_submit_admin_req (int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__*) ; 

int pqisrc_change_op_ibq_queue_prop(pqisrc_softstate_t *softs,
			ib_queue_t *op_ib_q, uint32_t prop)
{
	int ret = PQI_STATUS_SUCCESS;;
	gen_adm_req_iu_t admin_req;
	gen_adm_resp_iu_t admin_resp;

	memset(&admin_req, 0, sizeof(admin_req));
	memset(&admin_resp, 0, sizeof(admin_resp));
	
	DBG_FUNC("IN\n");
	
	admin_req.fn_code = PQI_FUNCTION_CHANGE_OPERATIONAL_IQ_PROP;
	admin_req.req_type.change_op_iq_prop.qid = op_ib_q->q_id;
	admin_req.req_type.change_op_iq_prop.vend_specific = prop;
	
	ret = pqisrc_submit_admin_req(softs, &admin_req, &admin_resp);
	
	DBG_FUNC("OUT\n");
	return ret;
}