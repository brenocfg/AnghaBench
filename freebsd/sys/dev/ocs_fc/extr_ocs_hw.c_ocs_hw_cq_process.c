#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ time_t ;
typedef  int sli4_qentry_e ;
typedef  int /*<<< orphan*/  sli4_mcqe_t ;
struct TYPE_21__ {int /*<<< orphan*/  sli; int /*<<< orphan*/  os; TYPE_2__** hw_wq; int /*<<< orphan*/  wq_hash; int /*<<< orphan*/  mq; } ;
typedef  TYPE_1__ ocs_hw_t ;
typedef  int int32_t ;
struct TYPE_22__ {int /*<<< orphan*/  wqec_set_count; } ;
typedef  TYPE_2__ hw_wq_t ;
struct TYPE_23__ {TYPE_4__* queue; } ;
typedef  TYPE_3__ hw_cq_t ;
struct TYPE_24__ {scalar_t__ proc_limit; scalar_t__ n_posted; scalar_t__ posted_limit; scalar_t__ max_num_processed; scalar_t__ max_process_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUTRACE (char*) ; 
 int /*<<< orphan*/  FALSE ; 
#define  SLI_QENTRY_ASYNC 135 
#define  SLI_QENTRY_MQ 134 
#define  SLI_QENTRY_OPT_WRITE_CMD 133 
#define  SLI_QENTRY_OPT_WRITE_DATA 132 
#define  SLI_QENTRY_RQ 131 
#define  SLI_QENTRY_WQ 130 
#define  SLI_QENTRY_WQ_RELEASE 129 
#define  SLI_QENTRY_XABT 128 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ UINT16_MAX ; 
 int /*<<< orphan*/  hw_wq_submit_pending (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_hw_mq_process (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int ocs_hw_queue_hash_find (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ocs_hw_rqpair_process_auto_xfr_rdy_cmd (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_hw_rqpair_process_auto_xfr_rdy_data (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_hw_rqpair_process_rq (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_hw_wq_process (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  ocs_hw_xabt_process (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 scalar_t__ ocs_msectime () ; 
 int sli_cq_parse (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int*,scalar_t__*) ; 
 int /*<<< orphan*/  sli_cqe_async (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sli_queue_arm (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sli_queue_read (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlikely (int) ; 

void
ocs_hw_cq_process(ocs_hw_t *hw, hw_cq_t *cq)
{
	uint8_t		cqe[sizeof(sli4_mcqe_t)];
	uint16_t	rid = UINT16_MAX;
	sli4_qentry_e	ctype;		/* completion type */
	int32_t		status;
	uint32_t	n_processed = 0;
	time_t		tstart;
	time_t		telapsed;

	tstart = ocs_msectime();

	while (!sli_queue_read(&hw->sli, cq->queue, cqe)) {
		status = sli_cq_parse(&hw->sli, cq->queue, cqe, &ctype, &rid);
		/*
		 * The sign of status is significant. If status is:
		 * == 0 : call completed correctly and the CQE indicated success
		 *  > 0 : call completed correctly and the CQE indicated an error
		 *  < 0 : call failed and no information is available about the CQE
		 */
		if (status < 0) {
			if (status == -2) {
				/* Notification that an entry was consumed, but not completed */
				continue;
			}

			break;
		}

		switch (ctype) {
		case SLI_QENTRY_ASYNC:
			CPUTRACE("async");
			sli_cqe_async(&hw->sli, cqe);
			break;
		case SLI_QENTRY_MQ:
			/*
			 * Process MQ entry. Note there is no way to determine
			 * the MQ_ID from the completion entry.
			 */
			CPUTRACE("mq");
			ocs_hw_mq_process(hw, status, hw->mq);
			break;
		case SLI_QENTRY_OPT_WRITE_CMD:
			ocs_hw_rqpair_process_auto_xfr_rdy_cmd(hw, cq, cqe);
			break;
		case SLI_QENTRY_OPT_WRITE_DATA:
			ocs_hw_rqpair_process_auto_xfr_rdy_data(hw, cq, cqe);
			break;
		case SLI_QENTRY_WQ:
			CPUTRACE("wq");
			ocs_hw_wq_process(hw, cq, cqe, status, rid);
			break;
		case SLI_QENTRY_WQ_RELEASE: {
			uint32_t wq_id = rid;
			int32_t index = ocs_hw_queue_hash_find(hw->wq_hash, wq_id);

			if (unlikely(index < 0)) {
				ocs_log_err(hw->os, "unknown idx=%#x rid=%#x\n",
					    index, rid);
				break;
			}

			hw_wq_t *wq = hw->hw_wq[index];

			/* Submit any HW IOs that are on the WQ pending list */
			hw_wq_submit_pending(wq, wq->wqec_set_count);

			break;
		}

		case SLI_QENTRY_RQ:
			CPUTRACE("rq");
			ocs_hw_rqpair_process_rq(hw, cq, cqe);
			break;
		case SLI_QENTRY_XABT: {
			CPUTRACE("xabt");
			ocs_hw_xabt_process(hw, cq, cqe, rid);
			break;

		}
		default:
			ocs_log_test(hw->os, "unhandled ctype=%#x rid=%#x\n", ctype, rid);
			break;
		}

		n_processed++;
		if (n_processed == cq->queue->proc_limit) {
			break;
		}

		if (cq->queue->n_posted >= (cq->queue->posted_limit)) {
			sli_queue_arm(&hw->sli, cq->queue, FALSE);
		}
	}

	sli_queue_arm(&hw->sli, cq->queue, TRUE);

	if (n_processed > cq->queue->max_num_processed) {
		cq->queue->max_num_processed = n_processed;
	}
	telapsed = ocs_msectime() - tstart;
	if (telapsed > cq->queue->max_process_time) {
		cq->queue->max_process_time = telapsed;
	}
}