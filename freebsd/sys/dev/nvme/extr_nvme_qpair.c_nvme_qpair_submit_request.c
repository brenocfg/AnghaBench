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
struct nvme_qpair {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  _nvme_qpair_submit_request (struct nvme_qpair*,struct nvme_request*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
nvme_qpair_submit_request(struct nvme_qpair *qpair, struct nvme_request *req)
{

	mtx_lock(&qpair->lock);
	_nvme_qpair_submit_request(qpair, req);
	mtx_unlock(&qpair->lock);
}