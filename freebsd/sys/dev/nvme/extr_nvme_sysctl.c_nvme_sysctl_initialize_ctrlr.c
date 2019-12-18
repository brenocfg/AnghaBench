#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct nvme_controller {int num_io_queues; int /*<<< orphan*/ * ioq; int /*<<< orphan*/  adminq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_S64 ; 
 int CTLTYPE_UINT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int QUEUE_NAME_LENGTH ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,struct nvme_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int*,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_sysctl_initialize_queue (int /*<<< orphan*/ *,struct sysctl_ctx_list*,struct sysctl_oid*) ; 
 int /*<<< orphan*/  nvme_sysctl_int_coal_threshold ; 
 int /*<<< orphan*/  nvme_sysctl_int_coal_time ; 
 int /*<<< orphan*/  nvme_sysctl_num_cmds ; 
 int /*<<< orphan*/  nvme_sysctl_num_failures ; 
 int /*<<< orphan*/  nvme_sysctl_num_intr_handler_calls ; 
 int /*<<< orphan*/  nvme_sysctl_num_retries ; 
 int /*<<< orphan*/  nvme_sysctl_reset_stats ; 
 int /*<<< orphan*/  nvme_sysctl_timeout_period ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

void
nvme_sysctl_initialize_ctrlr(struct nvme_controller *ctrlr)
{
	struct sysctl_ctx_list	*ctrlr_ctx;
	struct sysctl_oid	*ctrlr_tree, *que_tree;
	struct sysctl_oid_list	*ctrlr_list;
#define QUEUE_NAME_LENGTH	16
	char			queue_name[QUEUE_NAME_LENGTH];
	int			i;

	ctrlr_ctx = device_get_sysctl_ctx(ctrlr->dev);
	ctrlr_tree = device_get_sysctl_tree(ctrlr->dev);
	ctrlr_list = SYSCTL_CHILDREN(ctrlr_tree);

	SYSCTL_ADD_UINT(ctrlr_ctx, ctrlr_list, OID_AUTO, "num_io_queues",
	    CTLFLAG_RD, &ctrlr->num_io_queues, 0,
	    "Number of I/O queue pairs");

	SYSCTL_ADD_PROC(ctrlr_ctx, ctrlr_list, OID_AUTO,
	    "int_coal_time", CTLTYPE_UINT | CTLFLAG_RW, ctrlr, 0,
	    nvme_sysctl_int_coal_time, "IU",
	    "Interrupt coalescing timeout (in microseconds)");

	SYSCTL_ADD_PROC(ctrlr_ctx, ctrlr_list, OID_AUTO,
	    "int_coal_threshold", CTLTYPE_UINT | CTLFLAG_RW, ctrlr, 0,
	    nvme_sysctl_int_coal_threshold, "IU",
	    "Interrupt coalescing threshold");

	SYSCTL_ADD_PROC(ctrlr_ctx, ctrlr_list, OID_AUTO,
	    "timeout_period", CTLTYPE_UINT | CTLFLAG_RW, ctrlr, 0,
	    nvme_sysctl_timeout_period, "IU",
	    "Timeout period (in seconds)");

	SYSCTL_ADD_PROC(ctrlr_ctx, ctrlr_list, OID_AUTO,
	    "num_cmds", CTLTYPE_S64 | CTLFLAG_RD,
	    ctrlr, 0, nvme_sysctl_num_cmds, "IU",
	    "Number of commands submitted");

	SYSCTL_ADD_PROC(ctrlr_ctx, ctrlr_list, OID_AUTO,
	    "num_intr_handler_calls", CTLTYPE_S64 | CTLFLAG_RD,
	    ctrlr, 0, nvme_sysctl_num_intr_handler_calls, "IU",
	    "Number of times interrupt handler was invoked (will "
	    "typically be less than number of actual interrupts "
	    "generated due to coalescing)");

	SYSCTL_ADD_PROC(ctrlr_ctx, ctrlr_list, OID_AUTO,
	    "num_retries", CTLTYPE_S64 | CTLFLAG_RD,
	    ctrlr, 0, nvme_sysctl_num_retries, "IU",
	    "Number of commands retried");

	SYSCTL_ADD_PROC(ctrlr_ctx, ctrlr_list, OID_AUTO,
	    "num_failures", CTLTYPE_S64 | CTLFLAG_RD,
	    ctrlr, 0, nvme_sysctl_num_failures, "IU",
	    "Number of commands ending in failure after all retries");

	SYSCTL_ADD_PROC(ctrlr_ctx, ctrlr_list, OID_AUTO,
	    "reset_stats", CTLTYPE_UINT | CTLFLAG_RW, ctrlr, 0,
	    nvme_sysctl_reset_stats, "IU", "Reset statistics to zero");

	que_tree = SYSCTL_ADD_NODE(ctrlr_ctx, ctrlr_list, OID_AUTO, "adminq",
	    CTLFLAG_RD, NULL, "Admin Queue");

	nvme_sysctl_initialize_queue(&ctrlr->adminq, ctrlr_ctx, que_tree);

	for (i = 0; i < ctrlr->num_io_queues; i++) {
		snprintf(queue_name, QUEUE_NAME_LENGTH, "ioq%d", i);
		que_tree = SYSCTL_ADD_NODE(ctrlr_ctx, ctrlr_list, OID_AUTO,
		    queue_name, CTLFLAG_RD, NULL, "IO Queue");
		nvme_sysctl_initialize_queue(&ctrlr->ioq[i], ctrlr_ctx,
		    que_tree);
	}
}