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
typedef  int /*<<< orphan*/  uint32_t ;
struct pthread {scalar_t__ state; int flags; scalar_t__ tid; int /*<<< orphan*/  cycle; } ;

/* Variables and functions */
 scalar_t__ PS_DEAD ; 
 int /*<<< orphan*/  SIGCANCEL ; 
 int THR_FLAGS_NEED_SUSPEND ; 
 int THR_FLAGS_SUSPENDED ; 
 int /*<<< orphan*/  THR_THREAD_LOCK (struct pthread*,struct pthread*) ; 
 int /*<<< orphan*/  THR_THREAD_UNLOCK (struct pthread*,struct pthread*) ; 
 scalar_t__ TID_TERMINATED ; 
 int /*<<< orphan*/  _thr_send_sig (struct pthread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _thr_umtx_wait_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
suspend_common(struct pthread *curthread, struct pthread *thread,
	int waitok)
{
	uint32_t tmp;

	while (thread->state != PS_DEAD &&
	      !(thread->flags & THR_FLAGS_SUSPENDED)) {
		thread->flags |= THR_FLAGS_NEED_SUSPEND;
		/* Thread is in creation. */
		if (thread->tid == TID_TERMINATED)
			return (1);
		tmp = thread->cycle;
		_thr_send_sig(thread, SIGCANCEL);
		THR_THREAD_UNLOCK(curthread, thread);
		if (waitok) {
			_thr_umtx_wait_uint(&thread->cycle, tmp, NULL, 0);
			THR_THREAD_LOCK(curthread, thread);
		} else {
			THR_THREAD_LOCK(curthread, thread);
			return (0);
		}
	}

	return (1);
}