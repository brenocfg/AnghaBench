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
 int /*<<< orphan*/  THR_LIST_REMOVE (struct pthread*) ; 
 int /*<<< orphan*/  _thread_active_threads ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 

void
_thr_unlink(struct pthread *curthread, struct pthread *thread)
{
	THREAD_LIST_WRLOCK(curthread);
	THR_LIST_REMOVE(thread);
	THREAD_LIST_UNLOCK(curthread);
	atomic_add_int(&_thread_active_threads, -1);
}