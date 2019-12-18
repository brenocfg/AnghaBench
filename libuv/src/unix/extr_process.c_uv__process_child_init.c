#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; int /*<<< orphan*/  args; int /*<<< orphan*/  file; int /*<<< orphan*/ * env; int /*<<< orphan*/  uid; int /*<<< orphan*/  gid; int /*<<< orphan*/ * cwd; } ;
typedef  TYPE_1__ uv_process_options_t ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  F_DUPFD ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  SAVE_ERRNO (int /*<<< orphan*/ ) ; 
 int SIGKILL ; 
 int SIGKILLTHR ; 
 int SIGSTOP ; 
 int /*<<< orphan*/  SIG_DFL ; 
 scalar_t__ SIG_ERR ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int UV_PROCESS_DETACHED ; 
 int UV_PROCESS_SETGID ; 
 int UV_PROCESS_SETUID ; 
 int /*<<< orphan*/  UV__ERR (int) ; 
 int /*<<< orphan*/  _exit (int) ; 
 scalar_t__ chdir (int /*<<< orphan*/ *) ; 
 int dup2 (int,int) ; 
 int /*<<< orphan*/ * environ ; 
 int errno ; 
 int /*<<< orphan*/  execvp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ setgid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setgroups (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setsid () ; 
 scalar_t__ setuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 scalar_t__ signal (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__cloexec_fcntl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__close (int) ; 
 int /*<<< orphan*/  uv__nonblock_fcntl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__write_int (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uv__process_child_init(const uv_process_options_t* options,
                                   int stdio_count,
                                   int (*pipes)[2],
                                   int error_fd) {
  sigset_t set;
  int close_fd;
  int use_fd;
  int err;
  int fd;
  int n;

  if (options->flags & UV_PROCESS_DETACHED)
    setsid();

  /* First duplicate low numbered fds, since it's not safe to duplicate them,
   * they could get replaced. Example: swapping stdout and stderr; without
   * this fd 2 (stderr) would be duplicated into fd 1, thus making both
   * stdout and stderr go to the same fd, which was not the intention. */
  for (fd = 0; fd < stdio_count; fd++) {
    use_fd = pipes[fd][1];
    if (use_fd < 0 || use_fd >= fd)
      continue;
    pipes[fd][1] = fcntl(use_fd, F_DUPFD, stdio_count);
    if (pipes[fd][1] == -1) {
      uv__write_int(error_fd, UV__ERR(errno));
      _exit(127);
    }
  }

  for (fd = 0; fd < stdio_count; fd++) {
    close_fd = pipes[fd][0];
    use_fd = pipes[fd][1];

    if (use_fd < 0) {
      if (fd >= 3)
        continue;
      else {
        /* redirect stdin, stdout and stderr to /dev/null even if UV_IGNORE is
         * set
         */
        use_fd = open("/dev/null", fd == 0 ? O_RDONLY : O_RDWR);
        close_fd = use_fd;

        if (use_fd < 0) {
          uv__write_int(error_fd, UV__ERR(errno));
          _exit(127);
        }
      }
    }

    if (fd == use_fd)
      uv__cloexec_fcntl(use_fd, 0);
    else
      fd = dup2(use_fd, fd);

    if (fd == -1) {
      uv__write_int(error_fd, UV__ERR(errno));
      _exit(127);
    }

    if (fd <= 2)
      uv__nonblock_fcntl(fd, 0);

    if (close_fd >= stdio_count)
      uv__close(close_fd);
  }

  for (fd = 0; fd < stdio_count; fd++) {
    use_fd = pipes[fd][1];

    if (use_fd >= stdio_count)
      uv__close(use_fd);
  }

  if (options->cwd != NULL && chdir(options->cwd)) {
    uv__write_int(error_fd, UV__ERR(errno));
    _exit(127);
  }

  if (options->flags & (UV_PROCESS_SETUID | UV_PROCESS_SETGID)) {
    /* When dropping privileges from root, the `setgroups` call will
     * remove any extraneous groups. If we don't call this, then
     * even though our uid has dropped, we may still have groups
     * that enable us to do super-user things. This will fail if we
     * aren't root, so don't bother checking the return value, this
     * is just done as an optimistic privilege dropping function.
     */
    SAVE_ERRNO(setgroups(0, NULL));
  }

  if ((options->flags & UV_PROCESS_SETGID) && setgid(options->gid)) {
    uv__write_int(error_fd, UV__ERR(errno));
    _exit(127);
  }

  if ((options->flags & UV_PROCESS_SETUID) && setuid(options->uid)) {
    uv__write_int(error_fd, UV__ERR(errno));
    _exit(127);
  }

  if (options->env != NULL) {
    environ = options->env;
  }

  /* Reset signal disposition.  Use a hard-coded limit because NSIG
   * is not fixed on Linux: it's either 32, 34 or 64, depending on
   * whether RT signals are enabled.  We are not allowed to touch
   * RT signal handlers, glibc uses them internally.
   */
  for (n = 1; n < 32; n += 1) {
    if (n == SIGKILL || n == SIGSTOP)
      continue;  /* Can't be changed. */

#if defined(__HAIKU__)
    if (n == SIGKILLTHR)
      continue;  /* Can't be changed. */
#endif

    if (SIG_ERR != signal(n, SIG_DFL))
      continue;

    uv__write_int(error_fd, UV__ERR(errno));
    _exit(127);
  }

  /* Reset signal mask. */
  sigemptyset(&set);
  err = pthread_sigmask(SIG_SETMASK, &set, NULL);

  if (err != 0) {
    uv__write_int(error_fd, UV__ERR(err));
    _exit(127);
  }

  execvp(options->file, options->args);
  uv__write_int(error_fd, UV__ERR(errno));
  _exit(127);
}