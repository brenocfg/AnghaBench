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
struct urwlock {int rw_state; } ;
typedef  int int32_t ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ URWLOCK_READER_COUNT (int) ; 
 int URWLOCK_WRITE_OWNER ; 
 scalar_t__ atomic_cmpset_acq_32 (int*,int,int) ; 

__attribute__((used)) static inline int
_thr_rwlock_trywrlock(struct urwlock *rwlock)
{
	int32_t state;

	state = rwlock->rw_state;
	while ((state & URWLOCK_WRITE_OWNER) == 0 &&
	    URWLOCK_READER_COUNT(state) == 0) {
		if (atomic_cmpset_acq_32(&rwlock->rw_state, state,
		    state | URWLOCK_WRITE_OWNER))
			return (0);
		state = rwlock->rw_state;
	}

	return (EBUSY);
}