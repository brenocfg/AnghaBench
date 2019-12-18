#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_21__ {int /*<<< orphan*/  display_name; TYPE_2__* sport; struct TYPE_21__* ocs; } ;
typedef  TYPE_5__ ocs_t ;
typedef  TYPE_5__ ocs_node_t ;
struct TYPE_19__ {void* timeout; } ;
struct TYPE_20__ {TYPE_3__ els; } ;
struct TYPE_17__ {TYPE_8__* virt; } ;
struct TYPE_22__ {char* display_name; TYPE_4__ iparam; int /*<<< orphan*/  hio_type; TYPE_1__ els_req; void* els_callback_arg; int /*<<< orphan*/  els_callback; void* els_retries_remaining; void* els_timeout_sec; } ;
typedef  TYPE_7__ ocs_io_t ;
struct TYPE_23__ {int /*<<< orphan*/  common_service_parameters; scalar_t__ resv1; int /*<<< orphan*/  command_code; } ;
typedef  TYPE_8__ fc_plogi_payload_t ;
typedef  int /*<<< orphan*/  els_cb_t ;
struct TYPE_18__ {int /*<<< orphan*/  service_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_ELS_CMD_FDISC ; 
 int /*<<< orphan*/  OCS_ELS_ROLE_ORIGINATOR ; 
 int /*<<< orphan*/  OCS_HW_ELS_REQ ; 
 int /*<<< orphan*/  __ocs_els_init ; 
 int /*<<< orphan*/  node_els_trace () ; 
 int /*<<< orphan*/  ocs_assert (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_display_sparams (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_7__* ocs_els_io_alloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_io_transition (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_err (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  ocs_memcpy (TYPE_8__*,int /*<<< orphan*/ ,int) ; 

ocs_io_t *
ocs_send_fdisc(ocs_node_t *node, uint32_t timeout_sec, uint32_t retries,
	els_cb_t cb, void *cbarg)
{
	ocs_io_t *els;
	ocs_t *ocs;
	fc_plogi_payload_t *fdisc;

	ocs_assert(node, NULL);
	ocs_assert(node->ocs, NULL);
	ocs = node->ocs;

	node_els_trace();

	els = ocs_els_io_alloc(node, sizeof(*fdisc), OCS_ELS_ROLE_ORIGINATOR);
	if (els == NULL) {
		ocs_log_err(ocs, "IO alloc failed\n");
	} else {
		els->els_timeout_sec = timeout_sec;
		els->els_retries_remaining = retries;
		els->els_callback = cb;
		els->els_callback_arg = cbarg;
		els->display_name = "fdisc";

		/* Build FDISC request */
		fdisc = els->els_req.virt;

		ocs_memcpy(fdisc, node->sport->service_params, sizeof(*fdisc));
		fdisc->command_code = FC_ELS_CMD_FDISC;
		fdisc->resv1 = 0;

		ocs_display_sparams(node->display_name, "fdisc send req", 0, NULL, fdisc->common_service_parameters);

		els->hio_type = OCS_HW_ELS_REQ;
		els->iparam.els.timeout = timeout_sec;
		ocs_io_transition(els, __ocs_els_init, NULL);
	}
	return els;
}