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
struct async {int in; int out; scalar_t__ pid; int proc_in; int proc_out; int /*<<< orphan*/  tid; int /*<<< orphan*/  data; int /*<<< orphan*/  (* proc ) (int,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  async_die_counter ; 
 int /*<<< orphan*/  async_die_is_recursing ; 
 int /*<<< orphan*/  async_key ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  close_pair (int*) ; 
 int /*<<< orphan*/  die_async ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int error_errno (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  git_atexit_clear () ; 
 int /*<<< orphan*/  main_thread ; 
 int main_thread_set ; 
 int /*<<< orphan*/  mark_child_for_cleanup (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ pipe (int*) ; 
 int process_is_async ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct async*) ; 
 int /*<<< orphan*/  pthread_key_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  run_thread ; 
 int /*<<< orphan*/  set_cloexec (int) ; 
 int /*<<< orphan*/  set_die_is_recursing_routine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_die_routine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  stub1 (int,int,int /*<<< orphan*/ ) ; 

int start_async(struct async *async)
{
	int need_in, need_out;
	int fdin[2], fdout[2];
	int proc_in, proc_out;

	need_in = async->in < 0;
	if (need_in) {
		if (pipe(fdin) < 0) {
			if (async->out > 0)
				close(async->out);
			return error_errno("cannot create pipe");
		}
		async->in = fdin[1];
	}

	need_out = async->out < 0;
	if (need_out) {
		if (pipe(fdout) < 0) {
			if (need_in)
				close_pair(fdin);
			else if (async->in)
				close(async->in);
			return error_errno("cannot create pipe");
		}
		async->out = fdout[0];
	}

	if (need_in)
		proc_in = fdin[0];
	else if (async->in)
		proc_in = async->in;
	else
		proc_in = -1;

	if (need_out)
		proc_out = fdout[1];
	else if (async->out)
		proc_out = async->out;
	else
		proc_out = -1;

#ifdef NO_PTHREADS
	/* Flush stdio before fork() to avoid cloning buffers */
	fflush(NULL);

	async->pid = fork();
	if (async->pid < 0) {
		error_errno("fork (async) failed");
		goto error;
	}
	if (!async->pid) {
		if (need_in)
			close(fdin[1]);
		if (need_out)
			close(fdout[0]);
		git_atexit_clear();
		process_is_async = 1;
		exit(!!async->proc(proc_in, proc_out, async->data));
	}

	mark_child_for_cleanup(async->pid, NULL);

	if (need_in)
		close(fdin[0]);
	else if (async->in)
		close(async->in);

	if (need_out)
		close(fdout[1]);
	else if (async->out)
		close(async->out);
#else
	if (!main_thread_set) {
		/*
		 * We assume that the first time that start_async is called
		 * it is from the main thread.
		 */
		main_thread_set = 1;
		main_thread = pthread_self();
		pthread_key_create(&async_key, NULL);
		pthread_key_create(&async_die_counter, NULL);
		set_die_routine(die_async);
		set_die_is_recursing_routine(async_die_is_recursing);
	}

	if (proc_in >= 0)
		set_cloexec(proc_in);
	if (proc_out >= 0)
		set_cloexec(proc_out);
	async->proc_in = proc_in;
	async->proc_out = proc_out;
	{
		int err = pthread_create(&async->tid, NULL, run_thread, async);
		if (err) {
			error(_("cannot create async thread: %s"), strerror(err));
			goto error;
		}
	}
#endif
	return 0;

error:
	if (need_in)
		close_pair(fdin);
	else if (async->in)
		close(async->in);

	if (need_out)
		close_pair(fdout);
	else if (async->out)
		close(async->out);
	return -1;
}