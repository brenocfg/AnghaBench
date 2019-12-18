#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ocs_t ;
struct TYPE_16__ {int /*<<< orphan*/ * ocs; } ;
typedef  TYPE_4__ ocs_node_t ;
struct TYPE_15__ {TYPE_6__* virt; } ;
struct TYPE_13__ {int /*<<< orphan*/  timeout; scalar_t__ df_ctl; int /*<<< orphan*/  type; int /*<<< orphan*/  r_ctl; } ;
struct TYPE_14__ {TYPE_1__ fc_ct; } ;
struct TYPE_17__ {char* display_name; int /*<<< orphan*/  hio_type; TYPE_3__ els_req; void* els_callback_arg; int /*<<< orphan*/  els_callback; TYPE_2__ iparam; } ;
typedef  TYPE_5__ ocs_io_t ;
struct TYPE_18__ {int port_type; scalar_t__ area_id_scope; scalar_t__ domain_id_scope; int /*<<< orphan*/  hdr; } ;
typedef  TYPE_6__ fcct_gidpt_req_t ;
typedef  int /*<<< orphan*/  els_cb_t ;

/* Variables and functions */
 int /*<<< orphan*/  FC_GS_NAMESERVER_GID_PT ; 
 int /*<<< orphan*/  FC_RCTL_ELS ; 
 int /*<<< orphan*/  FC_TYPE_GS ; 
 scalar_t__ OCS_ELS_GID_PT_RSP_LEN ; 
 int /*<<< orphan*/  OCS_ELS_ROLE_ORIGINATOR ; 
 int /*<<< orphan*/  OCS_HW_FC_CT ; 
 int /*<<< orphan*/  __ocs_els_init ; 
 int /*<<< orphan*/  fcct_build_req_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  node_els_trace () ; 
 TYPE_5__* ocs_els_io_alloc_size (TYPE_4__*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_io_transition (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 

ocs_io_t *
ocs_ns_send_gidpt(ocs_node_t *node, uint32_t timeout_sec, uint32_t retries,
	els_cb_t cb, void *cbarg)
{
	ocs_io_t *els;
	ocs_t *ocs = node->ocs;
	fcct_gidpt_req_t *gidpt;

	node_els_trace();

	els = ocs_els_io_alloc_size(node, sizeof(*gidpt), OCS_ELS_GID_PT_RSP_LEN, OCS_ELS_ROLE_ORIGINATOR);
	if (els == NULL) {
		ocs_log_err(ocs, "IO alloc failed\n");
	} else {

		els->iparam.fc_ct.r_ctl = FC_RCTL_ELS;
		els->iparam.fc_ct.type = FC_TYPE_GS;
		els->iparam.fc_ct.df_ctl = 0;
		els->iparam.fc_ct.timeout = timeout_sec;

		els->els_callback = cb;
		els->els_callback_arg = cbarg;
		els->display_name = "gidpt";

		gidpt = els->els_req.virt;

		ocs_memset(gidpt, 0, sizeof(*gidpt));
		fcct_build_req_header(&gidpt->hdr, FC_GS_NAMESERVER_GID_PT, (OCS_ELS_GID_PT_RSP_LEN - sizeof(gidpt->hdr)) );
		gidpt->domain_id_scope = 0;
		gidpt->area_id_scope = 0;
		gidpt->port_type = 0x7f;

		els->hio_type = OCS_HW_FC_CT;

		ocs_io_transition(els, __ocs_els_init, NULL);
	}
	return els;
}