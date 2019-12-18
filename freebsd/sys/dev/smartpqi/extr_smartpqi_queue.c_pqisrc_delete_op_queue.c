#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  pqisrc_softstate_t ;
struct TYPE_8__ {int /*<<< orphan*/  qid; } ;
struct TYPE_9__ {TYPE_1__ create_op_iq; } ;
struct TYPE_10__ {int /*<<< orphan*/  fn_code; TYPE_2__ req_type; } ;
typedef  TYPE_3__ gen_adm_resp_iu_t ;
typedef  TYPE_3__ gen_adm_req_iu_t ;
typedef  scalar_t__ boolean_t ;
typedef  int /*<<< orphan*/  admin_resp ;
typedef  int /*<<< orphan*/  admin_req ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  PQI_FUNCTION_DELETE_OPERATIONAL_IQ ; 
 int /*<<< orphan*/  PQI_FUNCTION_DELETE_OPERATIONAL_OQ ; 
 int PQI_STATUS_SUCCESS ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int pqisrc_submit_admin_req (int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*) ; 

int pqisrc_delete_op_queue(pqisrc_softstate_t *softs,
				uint32_t q_id, boolean_t ibq)
{
	int ret = PQI_STATUS_SUCCESS;
	/* Firmware doesn't support this now */

#if 0
	gen_adm_req_iu_t admin_req;
	gen_adm_resp_iu_t admin_resp;


	memset(&admin_req, 0, sizeof(admin_req));
	memset(&admin_resp, 0, sizeof(admin_resp));

	DBG_FUNC("IN\n");

	admin_req.req_type.create_op_iq.qid = q_id;

	if (ibq)
		admin_req.fn_code = PQI_FUNCTION_DELETE_OPERATIONAL_IQ;
	else
		admin_req.fn_code = PQI_FUNCTION_DELETE_OPERATIONAL_OQ;
	
	
	ret = pqisrc_submit_admin_req(softs, &admin_req, &admin_resp);
	
	DBG_FUNC("OUT\n");
#endif
	return ret;
}