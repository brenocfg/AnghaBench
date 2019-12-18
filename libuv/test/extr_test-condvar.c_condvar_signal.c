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
struct TYPE_3__ {int /*<<< orphan*/  sem_signaled; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; scalar_t__ use_broadcast; int /*<<< orphan*/  sem_waiting; } ;
typedef  TYPE_1__ worker_config ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  uv_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_sem_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void condvar_signal(worker_config* c, int* flag) {
  /* Wait until waiter holds mutex and is preparing to wait. */
  uv_sem_wait(&c->sem_waiting);

  /* Make sure waiter has begun waiting. */
  uv_mutex_lock(&c->mutex);

  /* Help waiter differentiate between spurious and legitimate wakeup. */
  ASSERT(*flag == 0);
  *flag = 1;

  if (c->use_broadcast)
    uv_cond_broadcast(&c->cond);
  else
    uv_cond_signal(&c->cond);

  uv_mutex_unlock(&c->mutex);

  /* Done signaling. */
  uv_sem_post(&c->sem_signaled);
}