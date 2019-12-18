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
struct pthread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_LIST_UNLOCK (struct pthread*) ; 
 int /*<<< orphan*/  THREAD_LIST_WRLOCK (struct pthread*) ; 
 int /*<<< orphan*/  THR_GCLIST_ADD (struct pthread*) ; 
 int /*<<< orphan*/  THR_LIST_REMOVE (struct pthread*) ; 
 int /*<<< orphan*/  THR_REF_ADD (struct pthread*,struct pthread*) ; 
 int /*<<< orphan*/  THR_REF_DEL (struct pthread*,struct pthread*) ; 
 scalar_t__ THR_SHOULD_GC (struct pthread*) ; 
 int /*<<< orphan*/  THR_THREAD_LOCK (struct pthread*,struct pthread*) ; 
 int /*<<< orphan*/  THR_THREAD_UNLOCK (struct pthread*,struct pthread*) ; 

void
_thr_try_gc(struct pthread *curthread, struct pthread *thread)
{
	if (THR_SHOULD_GC(thread)) {
		THR_REF_ADD(curthread, thread);
		THR_THREAD_UNLOCK(curthread, thread);
		THREAD_LIST_WRLOCK(curthread);
		THR_THREAD_LOCK(curthread, thread);
		THR_REF_DEL(curthread, thread);
		if (THR_SHOULD_GC(thread)) {
			THR_LIST_REMOVE(thread);
			THR_GCLIST_ADD(thread);
		}
		THR_THREAD_UNLOCK(curthread, thread);
		THREAD_LIST_UNLOCK(curthread);
	} else {
		THR_THREAD_UNLOCK(curthread, thread);
	}
}