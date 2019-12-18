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
typedef  scalar_t__ u32 ;
struct request {int /*<<< orphan*/  tag; } ;
struct carm_request {scalar_t__ msg_bucket; int /*<<< orphan*/  msg_subtype; int /*<<< orphan*/  msg_type; } ;
struct carm_msg_ioctl {int /*<<< orphan*/  subtype; int /*<<< orphan*/  type; } ;
struct carm_host {int /*<<< orphan*/  oob_q; } ;
typedef  unsigned int (* carm_sspc_t ) (struct carm_host*,int /*<<< orphan*/ ,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct request*) ; 
 int /*<<< orphan*/  REQ_OP_DRV_OUT ; 
 int /*<<< orphan*/  blk_execute_rq_nowait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct request*,int,int /*<<< orphan*/ *) ; 
 struct request* blk_mq_alloc_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct carm_request* blk_mq_rq_to_pdu (struct request*) ; 
 int carm_lookup_bucket (unsigned int) ; 
 void* carm_ref_msg (struct carm_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int carm_send_special (struct carm_host *host, carm_sspc_t func)
{
	struct request *rq;
	struct carm_request *crq;
	struct carm_msg_ioctl *ioc;
	void *mem;
	unsigned int msg_size;
	int rc;

	rq = blk_mq_alloc_request(host->oob_q, REQ_OP_DRV_OUT, 0);
	if (IS_ERR(rq))
		return -ENOMEM;
	crq = blk_mq_rq_to_pdu(rq);

	mem = carm_ref_msg(host, rq->tag);

	msg_size = func(host, rq->tag, mem);

	ioc = mem;
	crq->msg_type = ioc->type;
	crq->msg_subtype = ioc->subtype;
	rc = carm_lookup_bucket(msg_size);
	BUG_ON(rc < 0);
	crq->msg_bucket = (u32) rc;

	DPRINTK("blk_execute_rq_nowait, tag == %u\n", rq->tag);
	blk_execute_rq_nowait(host->oob_q, NULL, rq, true, NULL);

	return 0;
}