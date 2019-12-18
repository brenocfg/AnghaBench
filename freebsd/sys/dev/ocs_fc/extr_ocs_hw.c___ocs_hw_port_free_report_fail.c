#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ocs_sm_event_t ;
struct TYPE_10__ {TYPE_4__* app; } ;
typedef  TYPE_3__ ocs_sm_ctx_t ;
struct TYPE_11__ {TYPE_5__* hw; } ;
typedef  TYPE_4__ ocs_sli_port_t ;
struct TYPE_9__ {int /*<<< orphan*/  port; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* port ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ;} ;
struct TYPE_12__ {TYPE_2__ args; TYPE_1__ callback; int /*<<< orphan*/  os; } ;
typedef  TYPE_5__ ocs_hw_t ;

/* Variables and functions */
#define  OCS_EVT_ENTER 128 
 int /*<<< orphan*/  OCS_HW_PORT_FREE_FAIL ; 
 int /*<<< orphan*/  SLI4_BMBX_SIZE ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smtrace (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void *
__ocs_hw_port_free_report_fail(ocs_sm_ctx_t *ctx, ocs_sm_event_t evt, void *data)
{
	ocs_sli_port_t	*sport = ctx->app;
	ocs_hw_t	*hw = sport->hw;

	smtrace("port");

	switch (evt) {
	case OCS_EVT_ENTER:
		if (data != NULL) {
			ocs_free(hw->os, data, SLI4_BMBX_SIZE);
		}
		if (hw->callback.port != NULL) {
			hw->callback.port(hw->args.port,
					OCS_HW_PORT_FREE_FAIL, sport);
		}
		break;
	default:
		break;
	}

	return NULL;
}