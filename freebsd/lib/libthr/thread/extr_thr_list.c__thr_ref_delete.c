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
struct pthread {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  THR_CRITICAL_LEAVE (struct pthread*) ; 
 int /*<<< orphan*/  THR_THREAD_LOCK (struct pthread*,struct pthread*) ; 
 int /*<<< orphan*/  _thr_try_gc (struct pthread*,struct pthread*) ; 

void
_thr_ref_delete(struct pthread *curthread, struct pthread *thread)
{
	THR_THREAD_LOCK(curthread, thread);
	thread->refcount--;
	_thr_try_gc(curthread, thread);
	THR_CRITICAL_LEAVE(curthread);
}