#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ocs_t ;
struct TYPE_19__ {TYPE_4__* sport; } ;
struct TYPE_20__ {TYPE_5__ rnode; int /*<<< orphan*/ * ocs; } ;
typedef  TYPE_6__ ocs_node_t ;
struct TYPE_17__ {TYPE_8__* virt; } ;
struct TYPE_15__ {int /*<<< orphan*/  timeout; scalar_t__ df_ctl; int /*<<< orphan*/  type; int /*<<< orphan*/  r_ctl; } ;
struct TYPE_16__ {TYPE_1__ fc_ct; } ;
struct TYPE_21__ {char* display_name; int /*<<< orphan*/  hio_type; TYPE_3__ els_req; void* els_callback_arg; int /*<<< orphan*/  els_callback; TYPE_2__ iparam; } ;
typedef  TYPE_7__ ocs_io_t ;
struct TYPE_22__ {void** fc4_types; void* port_id; int /*<<< orphan*/  hdr; } ;
typedef  TYPE_8__ fcct_rftid_req_t ;
typedef  int /*<<< orphan*/  els_cb_t ;
struct TYPE_18__ {int fc_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_GS_NAMESERVER_RFT_ID ; 
 int FC_GS_TYPE_BIT (int /*<<< orphan*/ ) ; 
 size_t FC_GS_TYPE_WORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FC_RCTL_ELS ; 
 int /*<<< orphan*/  FC_TYPE_FCP ; 
 int /*<<< orphan*/  FC_TYPE_GS ; 
 int /*<<< orphan*/  OCS_ELS_ROLE_ORIGINATOR ; 
 scalar_t__ OCS_ELS_RSP_LEN ; 
 int /*<<< orphan*/  OCS_HW_FC_CT ; 
 int /*<<< orphan*/  __ocs_els_init ; 
 int /*<<< orphan*/  fcct_build_req_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  node_els_trace () ; 
 TYPE_7__* ocs_els_io_alloc (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 void* ocs_htobe32 (int) ; 
 int /*<<< orphan*/  ocs_io_transition (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 

ocs_io_t *
ocs_ns_send_rftid(ocs_node_t *node, uint32_t timeout_sec, uint32_t retries,
	els_cb_t cb, void *cbarg)
{
	ocs_io_t *els;
	ocs_t *ocs = node->ocs;
	fcct_rftid_req_t *rftid;

	node_els_trace();

	els = ocs_els_io_alloc(node, sizeof(*rftid), OCS_ELS_ROLE_ORIGINATOR);
	if (els == NULL) {
		ocs_log_err(ocs, "IO alloc failed\n");
	} else {

		els->iparam.fc_ct.r_ctl = FC_RCTL_ELS;
		els->iparam.fc_ct.type = FC_TYPE_GS;
		els->iparam.fc_ct.df_ctl = 0;
		els->iparam.fc_ct.timeout = timeout_sec;

		els->els_callback = cb;
		els->els_callback_arg = cbarg;
		els->display_name = "rftid";

		rftid = els->els_req.virt;

		ocs_memset(rftid, 0, sizeof(*rftid));
		fcct_build_req_header(&rftid->hdr, FC_GS_NAMESERVER_RFT_ID, (OCS_ELS_RSP_LEN - sizeof(rftid->hdr)));
		rftid->port_id = ocs_htobe32(node->rnode.sport->fc_id);
		rftid->fc4_types[FC_GS_TYPE_WORD(FC_TYPE_FCP)] = ocs_htobe32(1 << FC_GS_TYPE_BIT(FC_TYPE_FCP));

		els->hio_type = OCS_HW_FC_CT;

		ocs_io_transition(els, __ocs_els_init, NULL);
	}
	return els;
}