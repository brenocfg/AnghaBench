#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int msg_queue; int /*<<< orphan*/ * items; int /*<<< orphan*/  member; } ;
typedef  TYPE_1__ uv__os390_epoll ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_RMID ; 
 int /*<<< orphan*/  QUEUE_REMOVE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  global_epoll_lock ; 
 int /*<<< orphan*/  msgctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_mutex_unlock (int /*<<< orphan*/ *) ; 

void epoll_queue_close(uv__os390_epoll* lst) {
  /* Remove epoll instance from global queue */
  uv_mutex_lock(&global_epoll_lock);
  QUEUE_REMOVE(&lst->member);
  uv_mutex_unlock(&global_epoll_lock);

  /* Free resources */
  msgctl(lst->msg_queue, IPC_RMID, NULL);
  lst->msg_queue = -1;
  uv__free(lst->items);
  lst->items = NULL;
}