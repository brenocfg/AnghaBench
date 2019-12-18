#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ibv_cq {TYPE_2__* context; struct ibv_comp_channel* channel; } ;
struct ibv_comp_channel {TYPE_3__* context; int /*<<< orphan*/  refcnt; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_4__ {int (* destroy_cq ) (struct ibv_cq*) ;} ;
struct TYPE_5__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct ibv_cq*) ; 

int __ibv_destroy_cq(struct ibv_cq *cq)
{
	struct ibv_comp_channel *channel = cq->channel;
	int ret;

	ret = cq->context->ops.destroy_cq(cq);

	if (channel) {
		if (!ret) {
			pthread_mutex_lock(&channel->context->mutex);
			--channel->refcnt;
			pthread_mutex_unlock(&channel->context->mutex);
		}
	}

	return ret;
}