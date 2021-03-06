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
struct urwlock {int dummy; } ;
struct timespec {int dummy; } ;

/* Variables and functions */
 int __thr_rwlock_rdlock (struct urwlock*,int,struct timespec*) ; 
 scalar_t__ _thr_rwlock_tryrdlock (struct urwlock*,int) ; 

__attribute__((used)) static inline int
_thr_rwlock_rdlock(struct urwlock *rwlock, int flags, struct timespec *tsp)
{

	if (_thr_rwlock_tryrdlock(rwlock, flags) == 0)
		return (0);
	return (__thr_rwlock_rdlock(rwlock, flags, tsp));
}