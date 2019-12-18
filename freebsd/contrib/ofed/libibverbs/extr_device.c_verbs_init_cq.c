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
struct ibv_cq {int /*<<< orphan*/  cond; int /*<<< orphan*/  mutex; scalar_t__ async_events_completed; scalar_t__ comp_events_completed; void* cq_context; struct ibv_comp_channel* channel; struct ibv_context* context; } ;
struct ibv_context {int /*<<< orphan*/  mutex; } ;
struct ibv_comp_channel {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void verbs_init_cq(struct ibv_cq *cq, struct ibv_context *context,
		       struct ibv_comp_channel *channel,
		       void *cq_context)
{
	cq->context		   = context;
	cq->channel		   = channel;

	if (cq->channel) {
		pthread_mutex_lock(&context->mutex);
		++cq->channel->refcnt;
		pthread_mutex_unlock(&context->mutex);
	}

	cq->cq_context		   = cq_context;
	cq->comp_events_completed  = 0;
	cq->async_events_completed = 0;
	pthread_mutex_init(&cq->mutex, NULL);
	pthread_cond_init(&cq->cond, NULL);
}