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

/* Variables and functions */
 int HASH_QUEUES ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 scalar_t__ _gc_count ; 
 int /*<<< orphan*/  _thr_list_lock ; 
 int /*<<< orphan*/  _thr_umutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _thr_urwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _thread_list ; 
 int /*<<< orphan*/  free_thread_lock ; 
 int /*<<< orphan*/  free_threadq ; 
 int inited ; 
 int /*<<< orphan*/  tcb_lock ; 
 int /*<<< orphan*/ * thr_hashtable ; 
 int total_threads ; 

void
_thr_list_init(void)
{
	int i;

	_gc_count = 0;
	total_threads = 1;
	_thr_urwlock_init(&_thr_list_lock);
	TAILQ_INIT(&_thread_list);
	TAILQ_INIT(&free_threadq);
	_thr_umutex_init(&free_thread_lock);
	_thr_umutex_init(&tcb_lock);
	if (inited) {
		for (i = 0; i < HASH_QUEUES; ++i)
			LIST_INIT(&thr_hashtable[i]);
	}
	inited = 1;
}