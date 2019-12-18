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
struct ub_ctx {int /*<<< orphan*/  rr_pipe; int /*<<< orphan*/  qq_pipe; int /*<<< orphan*/  bg_pid; int /*<<< orphan*/  cfglock; int /*<<< orphan*/  bg_tid; scalar_t__ dothread; } ;
struct libworker {int is_bg_thread; int thread_num; } ;

/* Variables and functions */
 int UB_FORKFAIL ; 
 int UB_NOERROR ; 
 int UB_NOMEM ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal_exit (char*) ; 
 int /*<<< orphan*/  fork () ; 
 int /*<<< orphan*/  libworker_dobg (struct libworker*) ; 
 struct libworker* libworker_setup (struct ub_ctx*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tube_close_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tube_close_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ub_thread_create (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (struct libworker*),struct libworker*) ; 

int libworker_bg(struct ub_ctx* ctx)
{
	struct libworker* w;
	/* fork or threadcreate */
	lock_basic_lock(&ctx->cfglock);
	if(ctx->dothread) {
		lock_basic_unlock(&ctx->cfglock);
		w = libworker_setup(ctx, 1, NULL);
		if(!w) return UB_NOMEM;
		w->is_bg_thread = 1;
#ifdef ENABLE_LOCK_CHECKS
		w->thread_num = 1; /* for nicer DEBUG checklocks */
#endif
		ub_thread_create(&ctx->bg_tid, libworker_dobg, w);
	} else {
		lock_basic_unlock(&ctx->cfglock);
#ifndef HAVE_FORK
		/* no fork on windows */
		return UB_FORKFAIL;
#else /* HAVE_FORK */
		switch((ctx->bg_pid=fork())) {
			case 0:
				w = libworker_setup(ctx, 1, NULL);
				if(!w) fatal_exit("out of memory");
				/* close non-used parts of the pipes */
				tube_close_write(ctx->qq_pipe);
				tube_close_read(ctx->rr_pipe);
				(void)libworker_dobg(w);
				exit(0);
				break;
			case -1:
				return UB_FORKFAIL;
			default:
				/* close non-used parts, so that the worker
				 * bgprocess gets 'pipe closed' when the
				 * main process exits */
				tube_close_read(ctx->qq_pipe);
				tube_close_write(ctx->rr_pipe);
				break;
		}
#endif /* HAVE_FORK */ 
	}
	return UB_NOERROR;
}