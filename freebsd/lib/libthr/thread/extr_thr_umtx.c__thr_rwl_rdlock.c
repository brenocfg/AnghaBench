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

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  PANIC (char*) ; 
 int /*<<< orphan*/  URWLOCK_PREFER_READER ; 
 int __thr_rwlock_rdlock (struct urwlock*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ _thr_rwlock_tryrdlock (struct urwlock*,int /*<<< orphan*/ ) ; 

void
_thr_rwl_rdlock(struct urwlock *rwlock)
{
	int ret;

	for (;;) {
		if (_thr_rwlock_tryrdlock(rwlock, URWLOCK_PREFER_READER) == 0)
			return;
		ret = __thr_rwlock_rdlock(rwlock, URWLOCK_PREFER_READER, NULL);
		if (ret == 0)
			return;
		if (ret != EINTR)
			PANIC("rdlock error");
	}
}