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
struct TYPE_3__ {int /*<<< orphan*/  sem_signaled; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; int /*<<< orphan*/  sem_waiting; } ;
typedef  TYPE_1__ worker_config ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int uv_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_sem_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int condvar_timedwait(worker_config* c, const int* flag) {
  int r;

  r = 0;

  uv_mutex_lock(&c->mutex);

  /* Tell signal'er that I am waiting. */
  uv_sem_post(&c->sem_waiting);

  /* Wait until I get a non-spurious signal. */
  do {
    r = uv_cond_timedwait(&c->cond, &c->mutex, (uint64_t)(1 * 1e9)); /* 1 s */
    ASSERT(r == 0); /* Should not time out. */
  } while (*flag == 0);
  ASSERT(*flag == 1);

  uv_mutex_unlock(&c->mutex);

  /* Wait for my signal'er to finish. */
  uv_sem_wait(&c->sem_signaled);
  return r;
}