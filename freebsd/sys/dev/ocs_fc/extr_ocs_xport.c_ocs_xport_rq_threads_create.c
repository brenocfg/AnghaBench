#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_12__ {int num_rq_threads; TYPE_6__* rq_thread_info; TYPE_2__* ocs; } ;
typedef  TYPE_1__ ocs_xport_t ;
typedef  int /*<<< orphan*/  ocs_xport_rq_thread_info_t ;
struct TYPE_13__ {int /*<<< orphan*/  instance_index; } ;
typedef  TYPE_2__ ocs_t ;
typedef  int int32_t ;
struct TYPE_14__ {int /*<<< orphan*/  thread_started; int /*<<< orphan*/  thread_name; int /*<<< orphan*/  thread; int /*<<< orphan*/ * seq_cbuf; TYPE_2__* ocs; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_HW_RQ_NUM_HDR ; 
 int /*<<< orphan*/  OCS_M_ZERO ; 
 int /*<<< orphan*/  OCS_THREAD_RUN ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * ocs_cbuf_alloc (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_debug (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  ocs_log_err (TYPE_2__*,char*,...) ; 
 TYPE_6__* ocs_malloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_snprintf (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int) ; 
 int ocs_thread_create (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_unsol_rq_thread ; 
 int /*<<< orphan*/  ocs_xport_rq_threads_teardown (TYPE_1__*) ; 

__attribute__((used)) static int32_t
ocs_xport_rq_threads_create(ocs_xport_t *xport, uint32_t num_rq_threads)
{
	ocs_t *ocs = xport->ocs;
	int32_t rc = 0;
	uint32_t i;

	xport->num_rq_threads = num_rq_threads;
	ocs_log_debug(ocs, "number of RQ threads %d\n", num_rq_threads);
	if (num_rq_threads == 0) {
		return 0;
	}

	/* Allocate the space for the thread objects */
	xport->rq_thread_info = ocs_malloc(ocs, sizeof(ocs_xport_rq_thread_info_t) * num_rq_threads, OCS_M_ZERO);
	if (xport->rq_thread_info == NULL) {
		ocs_log_err(ocs, "memory allocation failure\n");
		return -1;
	}

	/* Create the circular buffers and threads. */
	for (i = 0; i < num_rq_threads; i++) {
		xport->rq_thread_info[i].ocs = ocs;
		xport->rq_thread_info[i].seq_cbuf = ocs_cbuf_alloc(ocs, OCS_HW_RQ_NUM_HDR);
		if (xport->rq_thread_info[i].seq_cbuf == NULL) {
			goto ocs_xport_rq_threads_create_error;
		}

		ocs_snprintf(xport->rq_thread_info[i].thread_name,
			     sizeof(xport->rq_thread_info[i].thread_name),
			     "ocs_unsol_rq:%d:%d", ocs->instance_index, i);
		rc = ocs_thread_create(ocs, &xport->rq_thread_info[i].thread, ocs_unsol_rq_thread,
				       xport->rq_thread_info[i].thread_name,
				       &xport->rq_thread_info[i], OCS_THREAD_RUN);
		if (rc) {
			ocs_log_err(ocs, "ocs_thread_create failed: %d\n", rc);
			goto ocs_xport_rq_threads_create_error;
		}
		xport->rq_thread_info[i].thread_started = TRUE;
	}
	return 0;

ocs_xport_rq_threads_create_error:
	ocs_xport_rq_threads_teardown(xport);
	return -1;
}