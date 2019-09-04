#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  _pending; } ;
typedef  TYPE_1__ h2o_hostinfo_getaddr_req_t ;
struct TYPE_5__ {scalar_t__ num_threads_idle; scalar_t__ num_threads; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; int /*<<< orphan*/  pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  create_lookup_thread () ; 
 scalar_t__ h2o_hostinfo_max_threads ; 
 int /*<<< orphan*/  h2o_linklist_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__ queue ; 

__attribute__((used)) static void dispatch_hostinfo_getaddr(h2o_hostinfo_getaddr_req_t *req)
{
    pthread_mutex_lock(&queue.mutex);

    h2o_linklist_insert(&queue.pending, &req->_pending);

    if (queue.num_threads_idle == 0 && queue.num_threads < h2o_hostinfo_max_threads)
        create_lookup_thread();

    pthread_cond_signal(&queue.cond);
    pthread_mutex_unlock(&queue.mutex);
}