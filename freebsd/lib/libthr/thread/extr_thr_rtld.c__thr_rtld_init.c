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
typedef  int /*<<< orphan*/  ucontext_t ;
struct umtx {int dummy; } ;
struct pthread {int dummy; } ;
struct RtldLockInfo {int /*<<< orphan*/ * at_fork; int /*<<< orphan*/  thread_clr_flag; int /*<<< orphan*/  thread_set_flag; int /*<<< orphan*/  lock_release; int /*<<< orphan*/  wlock_acquire; int /*<<< orphan*/  rlock_acquire; int /*<<< orphan*/  lock_destroy; int /*<<< orphan*/  lock_create; } ;
typedef  int /*<<< orphan*/  dummy ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_getpid ; 
 int /*<<< orphan*/  UMTX_OP_WAKE ; 
 int /*<<< orphan*/  __error () ; 
 int /*<<< orphan*/  __fillcontextx2 (char*) ; 
 int __getcontextx_size () ; 
 struct pthread* _get_curthread () ; 
 int /*<<< orphan*/  _malloc_postfork () ; 
 int /*<<< orphan*/  _malloc_prefork () ; 
 int /*<<< orphan*/  _rtld_atfork_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtld_atfork_pre (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtld_get_stack_prot () ; 
 int /*<<< orphan*/  _rtld_thread_init (struct RtldLockInfo*) ; 
 int /*<<< orphan*/  _thr_rtld_clr_flag ; 
 int /*<<< orphan*/  _thr_rtld_lock_create ; 
 int /*<<< orphan*/  _thr_rtld_lock_destroy ; 
 int /*<<< orphan*/  _thr_rtld_lock_release ; 
 int /*<<< orphan*/  _thr_rtld_rlock_acquire ; 
 int /*<<< orphan*/  _thr_rtld_set_flag ; 
 int /*<<< orphan*/  _thr_rtld_wlock_acquire ; 
 int /*<<< orphan*/  _thr_signal_block (struct pthread*) ; 
 int /*<<< orphan*/  _thr_signal_unblock (struct pthread*) ; 
 int /*<<< orphan*/  _umtx_op_err (struct umtx*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * alloca (int) ; 
 int /*<<< orphan*/  getcontext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  memcpy (long*,long*,int) ; 
 int /*<<< orphan*/  mprotect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ) ; 

void
_thr_rtld_init(void)
{
	struct RtldLockInfo	li;
	struct pthread		*curthread;
	ucontext_t *uc;
	long dummy = -1;
	int uc_len;

	curthread = _get_curthread();

	/* force to resolve _umtx_op PLT */
	_umtx_op_err((struct umtx *)&dummy, UMTX_OP_WAKE, 1, 0, 0);
	
	/* force to resolve errno() PLT */
	__error();

	/* force to resolve memcpy PLT */
	memcpy(&dummy, &dummy, sizeof(dummy));

	mprotect(NULL, 0, 0);
	_rtld_get_stack_prot();

	li.lock_create  = _thr_rtld_lock_create;
	li.lock_destroy = _thr_rtld_lock_destroy;
	li.rlock_acquire = _thr_rtld_rlock_acquire;
	li.wlock_acquire = _thr_rtld_wlock_acquire;
	li.lock_release  = _thr_rtld_lock_release;
	li.thread_set_flag = _thr_rtld_set_flag;
	li.thread_clr_flag = _thr_rtld_clr_flag;
	li.at_fork = NULL;

	/*
	 * Preresolve the symbols needed for the fork interposer.  We
	 * call _rtld_atfork_pre() and _rtld_atfork_post() with NULL
	 * argument to indicate that no actual locking inside the
	 * functions should happen.  Neither rtld compat locks nor
	 * libthr rtld locks cannot work there:
	 * - compat locks do not handle the case of two locks taken
	 *   in write mode (the signal mask for the thread is corrupted);
	 * - libthr locks would work, but locked rtld_bind_lock prevents
	 *   symbol resolution for _rtld_atfork_post.
	 */
	_rtld_atfork_pre(NULL);
	_rtld_atfork_post(NULL);
	_malloc_prefork();
	_malloc_postfork();
	getpid();
	syscall(SYS_getpid);

	/* mask signals, also force to resolve __sys_sigprocmask PLT */
	_thr_signal_block(curthread);
	_rtld_thread_init(&li);
	_thr_signal_unblock(curthread);

	uc_len = __getcontextx_size();
	uc = alloca(uc_len);
	getcontext(uc);
	__fillcontextx2((char *)uc);
}