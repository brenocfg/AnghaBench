#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_10__ {int /*<<< orphan*/  thread_started; int /*<<< orphan*/  thread; int /*<<< orphan*/  seq_cbuf; int /*<<< orphan*/ * ocs; } ;
typedef  TYPE_2__ ocs_xport_rq_thread_info_t ;
struct TYPE_11__ {int /*<<< orphan*/  name; TYPE_2__* arg; } ;
typedef  TYPE_3__ ocs_thread_t ;
typedef  int /*<<< orphan*/  ocs_t ;
struct TYPE_12__ {TYPE_1__* hw; } ;
typedef  TYPE_4__ ocs_hw_sequence_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_9__ {scalar_t__ os; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ OCS_MAX_FRAMES_BEFORE_YEILDING ; 
 TYPE_4__* ocs_cbuf_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_thread_terminate_requested (TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_thread_yield (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_unsol_process (int /*<<< orphan*/ *,TYPE_4__*) ; 

int32_t
ocs_unsol_rq_thread(ocs_thread_t *mythread)
{
	ocs_xport_rq_thread_info_t *thread_data = mythread->arg;
	ocs_t *ocs = thread_data->ocs;
	ocs_hw_sequence_t *seq;
	uint32_t yield_count = OCS_MAX_FRAMES_BEFORE_YEILDING;

	ocs_log_debug(ocs, "%s running\n", mythread->name);
	while (!ocs_thread_terminate_requested(mythread)) {
		seq = ocs_cbuf_get(thread_data->seq_cbuf, 100000);
		if (seq == NULL) {
			/* Prevent soft lockups by yielding the CPU */
			ocs_thread_yield(&thread_data->thread);
			yield_count = OCS_MAX_FRAMES_BEFORE_YEILDING;
			continue;
		}
		/* Note: Always returns 0 */
		ocs_unsol_process((ocs_t*)seq->hw->os, seq);

		/* We have to prevent CPU soft lockups, so just yield the CPU after x frames. */
		if (--yield_count == 0) {
			ocs_thread_yield(&thread_data->thread);
			yield_count = OCS_MAX_FRAMES_BEFORE_YEILDING;
		}
	}
	ocs_log_debug(ocs, "%s exiting\n", mythread->name);
	thread_data->thread_started = FALSE;
	return 0;
}