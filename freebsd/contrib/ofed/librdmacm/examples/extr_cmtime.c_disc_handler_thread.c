#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct list_head {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; } ;

/* Variables and functions */
 scalar_t__ __list_empty (TYPE_1__*) ; 
 struct list_head* __list_remove_head (TYPE_1__*) ; 
 TYPE_1__ disc_work ; 
 int /*<<< orphan*/  free (struct list_head*) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_destroy_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_disconnect (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *disc_handler_thread(void *arg)
{
	struct list_head *work;
	do {
		pthread_mutex_lock(&disc_work.lock);
		if (__list_empty(&disc_work))
			pthread_cond_wait(&disc_work.cond, &disc_work.lock);
		work = __list_remove_head(&disc_work);
		pthread_mutex_unlock(&disc_work.lock);
		rdma_disconnect(work->id);
		rdma_destroy_id(work->id);
		free(work);
	} while (1);
	return NULL;
}