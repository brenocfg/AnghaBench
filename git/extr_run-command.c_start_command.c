#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ argv; } ;
struct TYPE_4__ {char** argv; } ;
struct child_process {char** argv; int in; int out; int err; int pid; scalar_t__ clean_on_exit; scalar_t__ silent_exec_failure; scalar_t__ dir; scalar_t__ env; scalar_t__ use_shell; scalar_t__ git_cmd; scalar_t__ stdout_to_stderr; scalar_t__ no_stdout; scalar_t__ no_stderr; scalar_t__ no_stdin; TYPE_1__ env_array; TYPE_2__ args; } ;
struct child_err {int dummy; } ;
struct atfork_state {int /*<<< orphan*/  old; } ;
struct argv_array {int /*<<< orphan*/ * argv; } ;
typedef  int /*<<< orphan*/  cerr ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  CHILD_ERR_CHDIR ; 
 int /*<<< orphan*/  CHILD_ERR_ENOENT ; 
 int /*<<< orphan*/  CHILD_ERR_ERRNO ; 
 int /*<<< orphan*/  CHILD_ERR_SIGPROCMASK ; 
 int /*<<< orphan*/  CHILD_ERR_SILENT ; 
 int ENOENT ; 
 int ENOEXEC ; 
 int NSIG ; 
 int O_CLOEXEC ; 
 int O_RDWR ; 
 scalar_t__ SIG_DFL ; 
 scalar_t__ SIG_IGN ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  atfork_parent (struct atfork_state*) ; 
 int /*<<< orphan*/  atfork_prepare (struct atfork_state*) ; 
 scalar_t__ chdir (scalar_t__) ; 
 int /*<<< orphan*/  child_close (int) ; 
 int /*<<< orphan*/  child_close_pair (int*) ; 
 int /*<<< orphan*/  child_die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  child_die_fn ; 
 int /*<<< orphan*/  child_dup2 (int,int) ; 
 int /*<<< orphan*/  child_err_spew (struct child_process*,struct child_err*) ; 
 int /*<<< orphan*/  child_error_fn ; 
 int child_notifier ; 
 int /*<<< orphan*/  child_process_clear (struct child_process*) ; 
 int /*<<< orphan*/  child_warn_fn ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  close_pair (int*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ) ; 
 int dup (int) ; 
 int errno ; 
 int /*<<< orphan*/  error (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_errno (char*,char*) ; 
 int /*<<< orphan*/  execve (int /*<<< orphan*/ ,char* const*,char* const*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int fork () ; 
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/  mark_child_for_cleanup (int,struct child_process*) ; 
 int mingw_spawnvpe (char*,char**,char**,scalar_t__,int,int,int) ; 
 int open (char*,int) ; 
 scalar_t__ pipe (int*) ; 
 char** prep_childenv (scalar_t__) ; 
 scalar_t__ prepare_cmd (struct argv_array*,struct child_process*) ; 
 char** prepare_git_cmd (struct argv_array*,char**) ; 
 char** prepare_shell_cmd (struct argv_array*,char**) ; 
 int /*<<< orphan*/  set_cloexec (int) ; 
 int /*<<< orphan*/  set_die_routine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_error_routine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_warn_routine (int /*<<< orphan*/ ) ; 
 scalar_t__ signal (int,scalar_t__) ; 
 scalar_t__ sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  trace2_child_exit (struct child_process*,int) ; 
 int /*<<< orphan*/  trace2_child_start (struct child_process*) ; 
 int /*<<< orphan*/  trace_run_command (struct child_process*) ; 
 int /*<<< orphan*/  wait_or_whine (int,char*,int /*<<< orphan*/ ) ; 
 int xread (int,struct child_err*,int) ; 

int start_command(struct child_process *cmd)
{
	int need_in, need_out, need_err;
	int fdin[2], fdout[2], fderr[2];
	int failed_errno;
	char *str;

	if (!cmd->argv)
		cmd->argv = cmd->args.argv;
	if (!cmd->env)
		cmd->env = cmd->env_array.argv;

	/*
	 * In case of errors we must keep the promise to close FDs
	 * that have been passed in via ->in and ->out.
	 */

	need_in = !cmd->no_stdin && cmd->in < 0;
	if (need_in) {
		if (pipe(fdin) < 0) {
			failed_errno = errno;
			if (cmd->out > 0)
				close(cmd->out);
			str = "standard input";
			goto fail_pipe;
		}
		cmd->in = fdin[1];
	}

	need_out = !cmd->no_stdout
		&& !cmd->stdout_to_stderr
		&& cmd->out < 0;
	if (need_out) {
		if (pipe(fdout) < 0) {
			failed_errno = errno;
			if (need_in)
				close_pair(fdin);
			else if (cmd->in)
				close(cmd->in);
			str = "standard output";
			goto fail_pipe;
		}
		cmd->out = fdout[0];
	}

	need_err = !cmd->no_stderr && cmd->err < 0;
	if (need_err) {
		if (pipe(fderr) < 0) {
			failed_errno = errno;
			if (need_in)
				close_pair(fdin);
			else if (cmd->in)
				close(cmd->in);
			if (need_out)
				close_pair(fdout);
			else if (cmd->out)
				close(cmd->out);
			str = "standard error";
fail_pipe:
			error("cannot create %s pipe for %s: %s",
				str, cmd->argv[0], strerror(failed_errno));
			child_process_clear(cmd);
			errno = failed_errno;
			return -1;
		}
		cmd->err = fderr[0];
	}

	trace2_child_start(cmd);
	trace_run_command(cmd);

	fflush(NULL);

#ifndef GIT_WINDOWS_NATIVE
{
	int notify_pipe[2];
	int null_fd = -1;
	char **childenv;
	struct argv_array argv = ARGV_ARRAY_INIT;
	struct child_err cerr;
	struct atfork_state as;

	if (prepare_cmd(&argv, cmd) < 0) {
		failed_errno = errno;
		cmd->pid = -1;
		if (!cmd->silent_exec_failure)
			error_errno("cannot run %s", cmd->argv[0]);
		goto end_of_spawn;
	}

	if (pipe(notify_pipe))
		notify_pipe[0] = notify_pipe[1] = -1;

	if (cmd->no_stdin || cmd->no_stdout || cmd->no_stderr) {
		null_fd = open("/dev/null", O_RDWR | O_CLOEXEC);
		if (null_fd < 0)
			die_errno(_("open /dev/null failed"));
		set_cloexec(null_fd);
	}

	childenv = prep_childenv(cmd->env);
	atfork_prepare(&as);

	/*
	 * NOTE: In order to prevent deadlocking when using threads special
	 * care should be taken with the function calls made in between the
	 * fork() and exec() calls.  No calls should be made to functions which
	 * require acquiring a lock (e.g. malloc) as the lock could have been
	 * held by another thread at the time of forking, causing the lock to
	 * never be released in the child process.  This means only
	 * Async-Signal-Safe functions are permitted in the child.
	 */
	cmd->pid = fork();
	failed_errno = errno;
	if (!cmd->pid) {
		int sig;
		/*
		 * Ensure the default die/error/warn routines do not get
		 * called, they can take stdio locks and malloc.
		 */
		set_die_routine(child_die_fn);
		set_error_routine(child_error_fn);
		set_warn_routine(child_warn_fn);

		close(notify_pipe[0]);
		set_cloexec(notify_pipe[1]);
		child_notifier = notify_pipe[1];

		if (cmd->no_stdin)
			child_dup2(null_fd, 0);
		else if (need_in) {
			child_dup2(fdin[0], 0);
			child_close_pair(fdin);
		} else if (cmd->in) {
			child_dup2(cmd->in, 0);
			child_close(cmd->in);
		}

		if (cmd->no_stderr)
			child_dup2(null_fd, 2);
		else if (need_err) {
			child_dup2(fderr[1], 2);
			child_close_pair(fderr);
		} else if (cmd->err > 1) {
			child_dup2(cmd->err, 2);
			child_close(cmd->err);
		}

		if (cmd->no_stdout)
			child_dup2(null_fd, 1);
		else if (cmd->stdout_to_stderr)
			child_dup2(2, 1);
		else if (need_out) {
			child_dup2(fdout[1], 1);
			child_close_pair(fdout);
		} else if (cmd->out > 1) {
			child_dup2(cmd->out, 1);
			child_close(cmd->out);
		}

		if (cmd->dir && chdir(cmd->dir))
			child_die(CHILD_ERR_CHDIR);

		/*
		 * restore default signal handlers here, in case
		 * we catch a signal right before execve below
		 */
		for (sig = 1; sig < NSIG; sig++) {
			/* ignored signals get reset to SIG_DFL on execve */
			if (signal(sig, SIG_DFL) == SIG_IGN)
				signal(sig, SIG_IGN);
		}

		if (sigprocmask(SIG_SETMASK, &as.old, NULL) != 0)
			child_die(CHILD_ERR_SIGPROCMASK);

		/*
		 * Attempt to exec using the command and arguments starting at
		 * argv.argv[1].  argv.argv[0] contains SHELL_PATH which will
		 * be used in the event exec failed with ENOEXEC at which point
		 * we will try to interpret the command using 'sh'.
		 */
		execve(argv.argv[1], (char *const *) argv.argv + 1,
		       (char *const *) childenv);
		if (errno == ENOEXEC)
			execve(argv.argv[0], (char *const *) argv.argv,
			       (char *const *) childenv);

		if (errno == ENOENT) {
			if (cmd->silent_exec_failure)
				child_die(CHILD_ERR_SILENT);
			child_die(CHILD_ERR_ENOENT);
		} else {
			child_die(CHILD_ERR_ERRNO);
		}
	}
	atfork_parent(&as);
	if (cmd->pid < 0)
		error_errno("cannot fork() for %s", cmd->argv[0]);
	else if (cmd->clean_on_exit)
		mark_child_for_cleanup(cmd->pid, cmd);

	/*
	 * Wait for child's exec. If the exec succeeds (or if fork()
	 * failed), EOF is seen immediately by the parent. Otherwise, the
	 * child process sends a child_err struct.
	 * Note that use of this infrastructure is completely advisory,
	 * therefore, we keep error checks minimal.
	 */
	close(notify_pipe[1]);
	if (xread(notify_pipe[0], &cerr, sizeof(cerr)) == sizeof(cerr)) {
		/*
		 * At this point we know that fork() succeeded, but exec()
		 * failed. Errors have been reported to our stderr.
		 */
		wait_or_whine(cmd->pid, cmd->argv[0], 0);
		child_err_spew(cmd, &cerr);
		failed_errno = errno;
		cmd->pid = -1;
	}
	close(notify_pipe[0]);

	if (null_fd >= 0)
		close(null_fd);
	argv_array_clear(&argv);
	free(childenv);
}
end_of_spawn:

#else
{
	int fhin = 0, fhout = 1, fherr = 2;
	const char **sargv = cmd->argv;
	struct argv_array nargv = ARGV_ARRAY_INIT;

	if (cmd->no_stdin)
		fhin = open("/dev/null", O_RDWR);
	else if (need_in)
		fhin = dup(fdin[0]);
	else if (cmd->in)
		fhin = dup(cmd->in);

	if (cmd->no_stderr)
		fherr = open("/dev/null", O_RDWR);
	else if (need_err)
		fherr = dup(fderr[1]);
	else if (cmd->err > 2)
		fherr = dup(cmd->err);

	if (cmd->no_stdout)
		fhout = open("/dev/null", O_RDWR);
	else if (cmd->stdout_to_stderr)
		fhout = dup(fherr);
	else if (need_out)
		fhout = dup(fdout[1]);
	else if (cmd->out > 1)
		fhout = dup(cmd->out);

	if (cmd->git_cmd)
		cmd->argv = prepare_git_cmd(&nargv, cmd->argv);
	else if (cmd->use_shell)
		cmd->argv = prepare_shell_cmd(&nargv, cmd->argv);

	cmd->pid = mingw_spawnvpe(cmd->argv[0], cmd->argv, (char**) cmd->env,
			cmd->dir, fhin, fhout, fherr);
	failed_errno = errno;
	if (cmd->pid < 0 && (!cmd->silent_exec_failure || errno != ENOENT))
		error_errno("cannot spawn %s", cmd->argv[0]);
	if (cmd->clean_on_exit && cmd->pid >= 0)
		mark_child_for_cleanup(cmd->pid, cmd);

	argv_array_clear(&nargv);
	cmd->argv = sargv;
	if (fhin != 0)
		close(fhin);
	if (fhout != 1)
		close(fhout);
	if (fherr != 2)
		close(fherr);
}
#endif

	if (cmd->pid < 0) {
		trace2_child_exit(cmd, -1);

		if (need_in)
			close_pair(fdin);
		else if (cmd->in)
			close(cmd->in);
		if (need_out)
			close_pair(fdout);
		else if (cmd->out)
			close(cmd->out);
		if (need_err)
			close_pair(fderr);
		else if (cmd->err)
			close(cmd->err);
		child_process_clear(cmd);
		errno = failed_errno;
		return -1;
	}

	if (need_in)
		close(fdin[0]);
	else if (cmd->in)
		close(cmd->in);

	if (need_out)
		close(fdout[1]);
	else if (cmd->out)
		close(cmd->out);

	if (need_err)
		close(fderr[1]);
	else if (cmd->err)
		close(cmd->err);

	return 0;
}