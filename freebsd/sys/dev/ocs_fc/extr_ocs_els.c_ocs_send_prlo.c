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
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  ocs_t ;
struct TYPE_16__ {int /*<<< orphan*/ * ocs; } ;
typedef  TYPE_4__ ocs_node_t ;
struct TYPE_14__ {void* timeout; } ;
struct TYPE_15__ {TYPE_2__ els; } ;
struct TYPE_13__ {TYPE_6__* virt; } ;
struct TYPE_17__ {char* display_name; TYPE_3__ iparam; int /*<<< orphan*/  hio_type; TYPE_1__ els_req; void* els_callback_arg; int /*<<< orphan*/  els_callback; void* els_retries_remaining; void* els_timeout_sec; } ;
typedef  TYPE_5__ ocs_io_t ;
struct TYPE_18__ {int page_length; scalar_t__ type_ext; int /*<<< orphan*/  type; int /*<<< orphan*/  payload_length; int /*<<< orphan*/  command_code; } ;
typedef  TYPE_6__ fc_prlo_payload_t ;
typedef  int /*<<< orphan*/  els_cb_t ;

/* Variables and functions */
 int /*<<< orphan*/  FC_ELS_CMD_PRLO ; 
 int /*<<< orphan*/  FC_TYPE_FCP ; 
 int /*<<< orphan*/  OCS_ELS_ROLE_ORIGINATOR ; 
 int /*<<< orphan*/  OCS_HW_ELS_REQ ; 
 int /*<<< orphan*/  __ocs_els_init ; 
 int /*<<< orphan*/  node_els_trace () ; 
 TYPE_5__* ocs_els_io_alloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_htobe16 (int) ; 
 int /*<<< orphan*/  ocs_io_transition (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 

ocs_io_t *
ocs_send_prlo(ocs_node_t *node, uint32_t timeout_sec, uint32_t retries,
	els_cb_t cb, void *cbarg)
{
	ocs_t *ocs = node->ocs;
	ocs_io_t *els;
	fc_prlo_payload_t *prlo;

	node_els_trace();

	els = ocs_els_io_alloc(node, sizeof(*prlo), OCS_ELS_ROLE_ORIGINATOR);
	if (els == NULL) {
		ocs_log_err(ocs, "IO alloc failed\n");
	} else {
		els->els_timeout_sec = timeout_sec;
		els->els_retries_remaining = retries;
		els->els_callback = cb;
		els->els_callback_arg = cbarg;
		els->display_name = "prlo";

		/* Build PRLO request */
		prlo = els->els_req.virt;

		ocs_memset(prlo, 0, sizeof(*prlo));
		prlo->command_code = FC_ELS_CMD_PRLO;
		prlo->page_length = 16;
		prlo->payload_length = ocs_htobe16(sizeof(fc_prlo_payload_t));
		prlo->type = FC_TYPE_FCP;
		prlo->type_ext = 0;

		els->hio_type = OCS_HW_ELS_REQ;
		els->iparam.els.timeout = timeout_sec;
		ocs_io_transition(els, __ocs_els_init, NULL);
	}
	return els;
}