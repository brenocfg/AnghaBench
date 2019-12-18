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
struct crypto_queue {scalar_t__ qlen; scalar_t__ max_qlen; int /*<<< orphan*/  list; int /*<<< orphan*/ * backlog; } ;
struct crypto_async_request {int flags; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 int ENOSPC ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int crypto_enqueue_request(struct crypto_queue *queue,
			   struct crypto_async_request *request)
{
	int err = -EINPROGRESS;

	if (unlikely(queue->qlen >= queue->max_qlen)) {
		if (!(request->flags & CRYPTO_TFM_REQ_MAY_BACKLOG)) {
			err = -ENOSPC;
			goto out;
		}
		err = -EBUSY;
		if (queue->backlog == &queue->list)
			queue->backlog = &request->list;
	}

	queue->qlen++;
	list_add_tail(&request->list, &queue->list);

out:
	return err;
}