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
struct cc_req_mgr_handle {int /*<<< orphan*/  q_free_slots; } ;
struct cc_hw_desc {int dummy; } ;
struct cc_drvdata {struct cc_req_mgr_handle* request_mgr_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSCRPTR_QUEUE_CONTENT ; 
 int /*<<< orphan*/  cc_ioread (struct cc_drvdata*,int /*<<< orphan*/ ) ; 
 int cc_queues_status (struct cc_drvdata*,struct cc_req_mgr_handle*,unsigned int) ; 
 int /*<<< orphan*/  enqueue_seq (struct cc_drvdata*,struct cc_hw_desc*,unsigned int) ; 
 int /*<<< orphan*/  set_queue_last_ind (struct cc_drvdata*,struct cc_hw_desc*) ; 
 int /*<<< orphan*/  wmb () ; 

int send_request_init(struct cc_drvdata *drvdata, struct cc_hw_desc *desc,
		      unsigned int len)
{
	struct cc_req_mgr_handle *req_mgr_h = drvdata->request_mgr_handle;
	unsigned int total_seq_len = len; /*initial sequence length*/
	int rc = 0;

	/* Wait for space in HW and SW FIFO. Poll for as much as FIFO_TIMEOUT.
	 */
	rc = cc_queues_status(drvdata, req_mgr_h, total_seq_len);
	if (rc)
		return rc;

	set_queue_last_ind(drvdata, &desc[(len - 1)]);

	/*
	 * We are about to push command to the HW via the command registers
	 * that may refernece hsot memory. We need to issue a memory barrier
	 * to make sure there are no outstnading memory writes
	 */
	wmb();
	enqueue_seq(drvdata, desc, len);

	/* Update the free slots in HW queue */
	req_mgr_h->q_free_slots =
		cc_ioread(drvdata, CC_REG(DSCRPTR_QUEUE_CONTENT));

	return 0;
}