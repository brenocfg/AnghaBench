#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * els; scalar_t__ ext_status; scalar_t__ status; } ;
typedef  TYPE_1__ ocs_node_cb_t ;
typedef  int /*<<< orphan*/  ocs_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_EVT_ELS_REQ_ABORTED ; 
 int /*<<< orphan*/  els_io_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ocs_els_io_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
ocs_els_abort_cleanup(ocs_io_t *els)
{
	/* handle event for ABORT_WQE
	 * whatever state ELS happened to be in, propagate aborted event up
	 * to node state machine in lieu of OCS_EVT_SRRS_ELS_* event
	 */
	ocs_node_cb_t cbdata;
	cbdata.status = cbdata.ext_status = 0;
	cbdata.els = els;
	els_io_printf(els, "Request aborted\n");
	ocs_els_io_cleanup(els, OCS_EVT_ELS_REQ_ABORTED, &cbdata);
}