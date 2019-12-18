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
struct urwlock {int rw_flags; int rw_state; } ;
typedef  int int32_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 scalar_t__ URWLOCK_MAX_READERS ; 
 int URWLOCK_PREFER_READER ; 
 scalar_t__ URWLOCK_READER_COUNT (int) ; 
 int URWLOCK_WRITE_OWNER ; 
 int URWLOCK_WRITE_WAITERS ; 
 scalar_t__ __predict_false (int) ; 
 scalar_t__ atomic_cmpset_acq_32 (int*,int,int) ; 

__attribute__((used)) static inline int
_thr_rwlock_tryrdlock(struct urwlock *rwlock, int flags)
{
	int32_t state, wrflags;

	if ((flags & URWLOCK_PREFER_READER) != 0 ||
	    (rwlock->rw_flags & URWLOCK_PREFER_READER) != 0)
		wrflags = URWLOCK_WRITE_OWNER;
	else
		wrflags = URWLOCK_WRITE_OWNER | URWLOCK_WRITE_WAITERS;
	state = rwlock->rw_state;
	while (!(state & wrflags)) {
		if (__predict_false(URWLOCK_READER_COUNT(state) ==
		    URWLOCK_MAX_READERS))
			return (EAGAIN);
		if (atomic_cmpset_acq_32(&rwlock->rw_state, state, state + 1))
			return (0);
		state = rwlock->rw_state;
	}

	return (EBUSY);
}