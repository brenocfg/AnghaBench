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
 int /*<<< orphan*/  __req_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct list_head*) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ req_work ; 

__attribute__((used)) static void *req_handler_thread(void *arg)
{
	struct list_head *work;
	do {
		pthread_mutex_lock(&req_work.lock);
		if (__list_empty(&req_work))
			pthread_cond_wait(&req_work.cond, &req_work.lock);
		work = __list_remove_head(&req_work);
		pthread_mutex_unlock(&req_work.lock);
		__req_handler(work->id);
		free(work);
	} while (1);
	return NULL;
}