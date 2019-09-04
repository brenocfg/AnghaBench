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

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ UV_EBUSY ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  rwlock ; 
 int /*<<< orphan*/  synchronize () ; 
 int /*<<< orphan*/  synchronize_nowait () ; 
 int /*<<< orphan*/  uv_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_rwlock_rdunlock (int /*<<< orphan*/ *) ; 
 scalar_t__ uv_rwlock_tryrdlock (int /*<<< orphan*/ *) ; 
 scalar_t__ uv_rwlock_trywrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_rwlock_wrunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void thread_rwlock_trylock_peer(void* unused) {
  (void) &unused;

  uv_mutex_lock(&mutex);

  /* Write lock held by other thread. */
  ASSERT(UV_EBUSY == uv_rwlock_tryrdlock(&rwlock));
  ASSERT(UV_EBUSY == uv_rwlock_trywrlock(&rwlock));
  synchronize();

  /* Read lock held by other thread. */
  ASSERT(0 == uv_rwlock_tryrdlock(&rwlock));
  uv_rwlock_rdunlock(&rwlock);
  ASSERT(UV_EBUSY == uv_rwlock_trywrlock(&rwlock));
  synchronize();

  /* Acquire write lock. */
  ASSERT(0 == uv_rwlock_trywrlock(&rwlock));
  synchronize();

  /* Release write lock and acquire read lock. */
  uv_rwlock_wrunlock(&rwlock);
  ASSERT(0 == uv_rwlock_tryrdlock(&rwlock));
  synchronize();

  uv_rwlock_rdunlock(&rwlock);
  synchronize_nowait();  /* Signal main thread we're going away. */
  uv_mutex_unlock(&mutex);
}