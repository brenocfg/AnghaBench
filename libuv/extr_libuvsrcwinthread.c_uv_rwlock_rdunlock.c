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

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSemaphore (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_fatal_error (int /*<<< orphan*/ ,char*) ; 

void uv_rwlock_rdunlock(uv_rwlock_t* rwlock) {
  EnterCriticalSection(&rwlock->state_.num_readers_lock_);

  if (--rwlock->state_.num_readers_ == 0) {
    if (!ReleaseSemaphore(rwlock->state_.write_semaphore_, 1, NULL))
      uv_fatal_error(GetLastError(), "ReleaseSemaphore");
  }

  LeaveCriticalSection(&rwlock->state_.num_readers_lock_);
}