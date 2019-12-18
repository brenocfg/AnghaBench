#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ocs_t ;
struct TYPE_20__ {TYPE_4__* sport; } ;
struct TYPE_22__ {TYPE_6__* sport; TYPE_5__ rnode; int /*<<< orphan*/ * ocs; } ;
typedef  TYPE_7__ ocs_node_t ;
struct TYPE_18__ {TYPE_9__* virt; } ;
struct TYPE_16__ {int /*<<< orphan*/  timeout; scalar_t__ df_ctl; int /*<<< orphan*/  type; int /*<<< orphan*/  r_ctl; } ;
struct TYPE_17__ {TYPE_1__ fc_ct; } ;
struct TYPE_23__ {char* display_name; int /*<<< orphan*/  hio_type; TYPE_3__ els_req; void* els_callback_arg; int /*<<< orphan*/  els_callback; TYPE_2__ iparam; } ;
typedef  TYPE_8__ ocs_io_t ;
struct TYPE_24__ {int /*<<< orphan*/  type; int /*<<< orphan*/  fc4_feature_bits; int /*<<< orphan*/  port_id; int /*<<< orphan*/  hdr; } ;
typedef  TYPE_9__ fcct_rffid_req_t ;
typedef  int /*<<< orphan*/  els_cb_t ;
struct TYPE_21__ {scalar_t__ enable_tgt; scalar_t__ enable_ini; } ;
struct TYPE_19__ {int /*<<< orphan*/  fc_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC4_FEATURE_INITIATOR ; 
 int /*<<< orphan*/  FC4_FEATURE_TARGET ; 
 int /*<<< orphan*/  FC_GS_NAMESERVER_RFF_ID ; 
 int /*<<< orphan*/  FC_RCTL_ELS ; 
 int /*<<< orphan*/  FC_TYPE_FCP ; 
 int /*<<< orphan*/  FC_TYPE_GS ; 
 int /*<<< orphan*/  OCS_ELS_ROLE_ORIGINATOR ; 
 scalar_t__ OCS_ELS_RSP_LEN ; 
 int /*<<< orphan*/  OCS_HW_FC_CT ; 
 int /*<<< orphan*/  __ocs_els_init ; 
 int /*<<< orphan*/  fcct_build_req_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  node_els_trace () ; 
 TYPE_8__* ocs_els_io_alloc (TYPE_7__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_htobe32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_io_transition (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_9__*,int /*<<< orphan*/ ,int) ; 

ocs_io_t *
ocs_ns_send_rffid(ocs_node_t *node, uint32_t timeout_sec, uint32_t retries,
	els_cb_t cb, void *cbarg)
{
	ocs_io_t *els;
	ocs_t *ocs = node->ocs;
	fcct_rffid_req_t *rffid;

	node_els_trace();

	els = ocs_els_io_alloc(node, sizeof(*rffid), OCS_ELS_ROLE_ORIGINATOR);
	if (els == NULL) {
		ocs_log_err(ocs, "IO alloc failed\n");
	} else {

		els->iparam.fc_ct.r_ctl = FC_RCTL_ELS;
		els->iparam.fc_ct.type = FC_TYPE_GS;
		els->iparam.fc_ct.df_ctl = 0;
		els->iparam.fc_ct.timeout = timeout_sec;

		els->els_callback = cb;
		els->els_callback_arg = cbarg;
		els->display_name = "rffid";

		rffid = els->els_req.virt;

		ocs_memset(rffid, 0, sizeof(*rffid));

		fcct_build_req_header(&rffid->hdr, FC_GS_NAMESERVER_RFF_ID, (OCS_ELS_RSP_LEN - sizeof(rffid->hdr)));
		rffid->port_id = ocs_htobe32(node->rnode.sport->fc_id);
		if (node->sport->enable_ini) {
			rffid->fc4_feature_bits |= FC4_FEATURE_INITIATOR;
		}
		if (node->sport->enable_tgt) {
			rffid->fc4_feature_bits |= FC4_FEATURE_TARGET;
		}
		rffid->type = FC_TYPE_FCP;

		els->hio_type = OCS_HW_FC_CT;

		ocs_io_transition(els, __ocs_els_init, NULL);
	}
	return els;
}