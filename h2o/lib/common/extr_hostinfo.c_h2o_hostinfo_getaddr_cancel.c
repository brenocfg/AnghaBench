#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * _cb; int /*<<< orphan*/  _pending; } ;
typedef  TYPE_1__ h2o_hostinfo_getaddr_req_t ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ h2o_linklist_is_linked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_linklist_unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__ queue ; 

void h2o_hostinfo_getaddr_cancel(h2o_hostinfo_getaddr_req_t *req)
{
    int should_free = 0;

    pthread_mutex_lock(&queue.mutex);

    if (h2o_linklist_is_linked(&req->_pending)) {
        h2o_linklist_unlink(&req->_pending);
        should_free = 1;
    } else {
        req->_cb = NULL;
    }

    pthread_mutex_unlock(&queue.mutex);

    if (should_free)
        free(req);
}