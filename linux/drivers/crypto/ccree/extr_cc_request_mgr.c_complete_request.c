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
struct cc_req_mgr_handle {int /*<<< orphan*/  comptask; int /*<<< orphan*/  compwork; int /*<<< orphan*/  workq; } ;
struct cc_drvdata {int /*<<< orphan*/  hw_queue_avail; struct cc_req_mgr_handle* request_mgr_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

void complete_request(struct cc_drvdata *drvdata)
{
	struct cc_req_mgr_handle *request_mgr_handle =
						drvdata->request_mgr_handle;

	complete(&drvdata->hw_queue_avail);
#ifdef COMP_IN_WQ
	queue_delayed_work(request_mgr_handle->workq,
			   &request_mgr_handle->compwork, 0);
#else
	tasklet_schedule(&request_mgr_handle->comptask);
#endif
}