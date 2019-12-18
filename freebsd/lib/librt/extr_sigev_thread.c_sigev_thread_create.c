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
struct sigev_thread {int tn_refcount; int tn_lwpid; int /*<<< orphan*/  tn_cv; int /*<<< orphan*/  tn_thread; int /*<<< orphan*/ * tn_cur; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct sigev_thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct sigev_thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGBUS ; 
 int /*<<< orphan*/  SIGFPE ; 
 int /*<<< orphan*/  SIGILL ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  __sigev_list_lock () ; 
 int /*<<< orphan*/  __sigev_list_unlock () ; 
 int /*<<< orphan*/  _pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int _pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sigev_thread*) ; 
 int /*<<< orphan*/  _sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct sigev_thread*) ; 
 struct sigev_thread* malloc (int) ; 
 int /*<<< orphan*/  sigdelset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigev_default_attr ; 
 struct sigev_thread* sigev_default_thread ; 
 int /*<<< orphan*/  sigev_list_mtx ; 
 int /*<<< orphan*/  sigev_service_loop ; 
 int /*<<< orphan*/  sigev_threads ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tn_link ; 

__attribute__((used)) static struct sigev_thread *
sigev_thread_create(int usedefault)
{
	struct sigev_thread *tn;
	sigset_t set, oset;
	int ret;

	if (usedefault && sigev_default_thread) {
		__sigev_list_lock();
		sigev_default_thread->tn_refcount++;
		__sigev_list_unlock();
		return (sigev_default_thread);	
	}

	tn = malloc(sizeof(*tn));
	tn->tn_cur = NULL;
	tn->tn_lwpid = -1;
	tn->tn_refcount = 1;
	_pthread_cond_init(&tn->tn_cv, NULL);

	/* for debug */
	__sigev_list_lock();
	LIST_INSERT_HEAD(&sigev_threads, tn, tn_link);
	__sigev_list_unlock();

	sigfillset(&set);	/* SIGLIBRT is masked. */
	sigdelset(&set, SIGBUS);
	sigdelset(&set, SIGILL);
	sigdelset(&set, SIGFPE);
	sigdelset(&set, SIGSEGV);
	sigdelset(&set, SIGTRAP);
	_sigprocmask(SIG_SETMASK, &set, &oset);
	ret = _pthread_create(&tn->tn_thread, &sigev_default_attr,
		 sigev_service_loop, tn);
	_sigprocmask(SIG_SETMASK, &oset, NULL);

	if (ret != 0) {
		__sigev_list_lock();
		LIST_REMOVE(tn, tn_link);
		__sigev_list_unlock();
		free(tn);
		tn = NULL;
	} else {
		/* wait the thread to get its lwpid */

		__sigev_list_lock();
		while (tn->tn_lwpid == -1)
			_pthread_cond_wait(&tn->tn_cv, sigev_list_mtx);
		__sigev_list_unlock();
	}
	return (tn);
}