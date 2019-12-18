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
struct bsg_job {int result; unsigned int reply_payload_rcv_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_complete_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_rq_from_pdu (struct bsg_job*) ; 

void bsg_job_done(struct bsg_job *job, int result,
		  unsigned int reply_payload_rcv_len)
{
	job->result = result;
	job->reply_payload_rcv_len = reply_payload_rcv_len;
	blk_mq_complete_request(blk_mq_rq_from_pdu(job));
}