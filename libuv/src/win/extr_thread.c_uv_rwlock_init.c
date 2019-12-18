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
struct TYPE_4__ {scalar_t__ num_readers_; int /*<<< orphan*/  num_readers_lock_; int /*<<< orphan*/ * write_semaphore_; } ;
struct TYPE_5__ {TYPE_1__ state_; } ;
typedef  TYPE_2__ uv_rwlock_t ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateSemaphoreW (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  InitializeCriticalSection (int /*<<< orphan*/ *) ; 
 int uv_translate_sys_error (int /*<<< orphan*/ ) ; 

int uv_rwlock_init(uv_rwlock_t* rwlock) {
  /* Initialize the semaphore that acts as the write lock. */
  HANDLE handle = CreateSemaphoreW(NULL, 1, 1, NULL);
  if (handle == NULL)
    return uv_translate_sys_error(GetLastError());
  rwlock->state_.write_semaphore_ = handle;

  /* Initialize the critical section protecting the reader count. */
  InitializeCriticalSection(&rwlock->state_.num_readers_lock_);

  /* Initialize the reader count. */
  rwlock->state_.num_readers_ = 0;

  return 0;
}