#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ibv_cq {TYPE_1__* context; } ;
struct c4iw_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/ ** cqid2ptr; } ;
struct TYPE_4__ {int error; size_t cqid; struct c4iw_cq* sw_queue; int /*<<< orphan*/  memsize; int /*<<< orphan*/  queue; int /*<<< orphan*/  ugts; } ;
struct c4iw_cq {TYPE_2__ cq; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c4iw_page_size ; 
 int /*<<< orphan*/  free (struct c4iw_cq*) ; 
 int ibv_cmd_destroy_cq (struct ibv_cq*) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_spin_unlock (int /*<<< orphan*/ *) ; 
 struct c4iw_cq* to_c4iw_cq (struct ibv_cq*) ; 
 struct c4iw_dev* to_c4iw_dev (int /*<<< orphan*/ ) ; 

int c4iw_destroy_cq(struct ibv_cq *ibcq)
{
	int ret;
	struct c4iw_cq *chp = to_c4iw_cq(ibcq);
	struct c4iw_dev *dev = to_c4iw_dev(ibcq->context->device);

	chp->cq.error = 1;
	ret = ibv_cmd_destroy_cq(ibcq);
	if (ret) {
		return ret;
	}
	munmap(MASKED(chp->cq.ugts), c4iw_page_size);
	munmap(chp->cq.queue, chp->cq.memsize);

	pthread_spin_lock(&dev->lock);
	dev->cqid2ptr[chp->cq.cqid] = NULL;
	pthread_spin_unlock(&dev->lock);

	free(chp->cq.sw_queue);
	free(chp);
	return 0;
}