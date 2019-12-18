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
struct nvme_request {int dummy; } ;
struct nvme_qpair {int dummy; } ;
struct nvme_controller {struct nvme_qpair* ioq; } ;

/* Variables and functions */
 size_t QP (struct nvme_controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curcpu ; 
 int /*<<< orphan*/  nvme_qpair_submit_request (struct nvme_qpair*,struct nvme_request*) ; 

void
nvme_ctrlr_submit_io_request(struct nvme_controller *ctrlr,
    struct nvme_request *req)
{
	struct nvme_qpair       *qpair;

	qpair = &ctrlr->ioq[QP(ctrlr, curcpu)];
	nvme_qpair_submit_request(qpair, req);
}