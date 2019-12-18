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
struct request {int dummy; } ;
struct bsg_job {int dummy; } ;

/* Variables and functions */
 struct bsg_job* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  bsg_job_put (struct bsg_job*) ; 

__attribute__((used)) static void bsg_complete(struct request *rq)
{
	struct bsg_job *job = blk_mq_rq_to_pdu(rq);

	bsg_job_put(job);
}