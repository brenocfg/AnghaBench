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
struct TYPE_4__ {scalar_t__ num_readers_; int /*<<< orphan*/  num_readers_lock_; int /*<<< orphan*/  write_semaphore_; } ;
struct TYPE_5__ {TYPE_1__ state_; } ;
typedef  TYPE_2__ uv_rwlock_t ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TryEnterCriticalSection (int /*<<< orphan*/ *) ; 
 int UV_EBUSY ; 
 scalar_t__ WAIT_FAILED ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WAIT_TIMEOUT ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_fatal_error (int /*<<< orphan*/ ,char*) ; 

int uv_rwlock_tryrdlock(uv_rwlock_t* rwlock) {
  int err;

  if (!TryEnterCriticalSection(&rwlock->state_.num_readers_lock_))
    return UV_EBUSY;

  err = 0;

  if (rwlock->state_.num_readers_ == 0) {
    /* Currently there are no other readers, which means that the write lock
     * needs to be acquired.
     */
    DWORD r = WaitForSingleObject(rwlock->state_.write_semaphore_, 0);
    if (r == WAIT_OBJECT_0)
      rwlock->state_.num_readers_++;
    else if (r == WAIT_TIMEOUT)
      err = UV_EBUSY;
    else if (r == WAIT_FAILED)
      uv_fatal_error(GetLastError(), "WaitForSingleObject");

  } else {
    /* The write lock has already been acquired because there are other
     * active readers.
     */
    rwlock->state_.num_readers_++;
  }

  LeaveCriticalSection(&rwlock->state_.num_readers_lock_);
  return err;
}