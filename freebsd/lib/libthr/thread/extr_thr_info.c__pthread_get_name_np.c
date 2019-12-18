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
struct pthread {scalar_t__ state; } ;
typedef  struct pthread* pthread_t ;

/* Variables and functions */
 scalar_t__ PS_DEAD ; 
 int /*<<< orphan*/  THR_THREAD_LOCK (struct pthread*,struct pthread*) ; 
 int /*<<< orphan*/  THR_THREAD_UNLOCK (struct pthread*,struct pthread*) ; 
 struct pthread* _get_curthread () ; 
 scalar_t__ _thr_find_thread (struct pthread*,struct pthread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thr_get_name_np (struct pthread*,char*,size_t) ; 

void
_pthread_get_name_np(pthread_t thread, char *buf, size_t len)
{
	struct pthread *curthread;

	curthread = _get_curthread();
	if (curthread == thread) {
		THR_THREAD_LOCK(curthread, thread);
		thr_get_name_np(thread, buf, len);
		THR_THREAD_UNLOCK(curthread, thread);
	} else {
		if (_thr_find_thread(curthread, thread, 0) == 0) {
			if (thread->state != PS_DEAD)
				thr_get_name_np(thread, buf, len);
			THR_THREAD_UNLOCK(curthread, thread);
		} else if (len > 0)
			buf[0] = '\0';
	}
}