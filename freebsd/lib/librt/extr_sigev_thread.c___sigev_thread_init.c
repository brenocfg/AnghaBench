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
typedef  int /*<<< orphan*/  pthread_mutexattr_t ;
typedef  int /*<<< orphan*/  pthread_mutex_t ;

/* Variables and functions */
 int HASH_QUEUES ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PTHREAD_CREATE_DETACHED ; 
 int /*<<< orphan*/  PTHREAD_MUTEX_NORMAL ; 
 int /*<<< orphan*/  PTHREAD_SCOPE_SYSTEM ; 
 int /*<<< orphan*/  __sigev_fork_child ; 
 int /*<<< orphan*/  __sigev_fork_parent ; 
 int /*<<< orphan*/  __sigev_fork_prepare ; 
 int /*<<< orphan*/  _pthread_atfork (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pthread_attr_setscope (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pthread_mutex_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _pthread_mutexattr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _pthread_mutexattr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _pthread_mutexattr_settype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int atfork_registered ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  sigev_all ; 
 int /*<<< orphan*/  sigev_default_attr ; 
 int /*<<< orphan*/ * sigev_default_thread ; 
 int /*<<< orphan*/ * sigev_hash ; 
 int /*<<< orphan*/  sigev_list_mtx ; 
 int /*<<< orphan*/ * sigev_thread_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigev_threads ; 

void
__sigev_thread_init(void)
{
	static int inited = 0;
	pthread_mutexattr_t mattr;
	int i;

	_pthread_mutexattr_init(&mattr);
	_pthread_mutexattr_settype(&mattr, PTHREAD_MUTEX_NORMAL);
	sigev_list_mtx = malloc(sizeof(pthread_mutex_t));
	_pthread_mutex_init(sigev_list_mtx, &mattr);
	_pthread_mutexattr_destroy(&mattr);

	for (i = 0; i < HASH_QUEUES; ++i)
		LIST_INIT(&sigev_hash[i]);
	LIST_INIT(&sigev_all);
	LIST_INIT(&sigev_threads);
	sigev_default_thread = NULL;
	if (atfork_registered == 0) {
		_pthread_atfork(
			__sigev_fork_prepare,
			__sigev_fork_parent,
			__sigev_fork_child);
		atfork_registered = 1;
	}
	if (!inited) {
		_pthread_attr_init(&sigev_default_attr);
		_pthread_attr_setscope(&sigev_default_attr,
			PTHREAD_SCOPE_SYSTEM);
		_pthread_attr_setdetachstate(&sigev_default_attr,
			PTHREAD_CREATE_DETACHED);
		inited = 1;
	}
	sigev_default_thread = sigev_thread_create(0);
}