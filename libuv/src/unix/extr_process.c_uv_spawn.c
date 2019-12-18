#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int pid; int /*<<< orphan*/  exit_cb; int /*<<< orphan*/  queue; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ uv_process_t ;
struct TYPE_14__ {int flags; int stdio_count; TYPE_7__* stdio; int /*<<< orphan*/  exit_cb; int /*<<< orphan*/ * file; } ;
typedef  TYPE_2__ uv_process_options_t ;
struct TYPE_15__ {int /*<<< orphan*/  process_handles; int /*<<< orphan*/  cloexec_lock; int /*<<< orphan*/  child_watcher; } ;
typedef  TYPE_3__ uv_loop_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  int ssize_t ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  exec_errorno ;
struct TYPE_16__ {int flags; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int**) ; 
 scalar_t__ EINTR ; 
 scalar_t__ EPIPE ; 
 int /*<<< orphan*/  QUEUE_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QUEUE_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int UV_ENOMEM ; 
 int UV_ENOSYS ; 
 int UV_INHERIT_FD ; 
 int UV_INHERIT_STREAM ; 
 int /*<<< orphan*/  UV_PROCESS ; 
 int UV_PROCESS_DETACHED ; 
 int UV_PROCESS_SETGID ; 
 int UV_PROCESS_SETUID ; 
 int UV_PROCESS_WINDOWS_HIDE ; 
 int UV_PROCESS_WINDOWS_HIDE_CONSOLE ; 
 int UV_PROCESS_WINDOWS_HIDE_GUI ; 
 int UV_PROCESS_WINDOWS_VERBATIM_ARGUMENTS ; 
 int UV__ERR (scalar_t__) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int fork () ; 
 int read (int,int*,int) ; 
 int /*<<< orphan*/  uv__chld ; 
 int /*<<< orphan*/  uv__close (int) ; 
 int /*<<< orphan*/  uv__close_nocheckstdio (int) ; 
 int /*<<< orphan*/  uv__free (int**) ; 
 int /*<<< orphan*/  uv__handle_init (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__handle_start (TYPE_1__*) ; 
 int uv__make_pipe (int*,int /*<<< orphan*/ ) ; 
 int** uv__malloc (int) ; 
 int /*<<< orphan*/  uv__process_child_init (TYPE_2__ const*,int,int**,int) ; 
 int /*<<< orphan*/  uv__process_close_stream (TYPE_7__*) ; 
 int uv__process_init_stdio (TYPE_7__*,int*) ; 
 int uv__process_open_stream (TYPE_7__*,int*) ; 
 int /*<<< orphan*/  uv_rwlock_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_rwlock_wrunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_signal_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

int uv_spawn(uv_loop_t* loop,
             uv_process_t* process,
             const uv_process_options_t* options) {
#if defined(__APPLE__) && (TARGET_OS_TV || TARGET_OS_WATCH)
  /* fork is marked __WATCHOS_PROHIBITED __TVOS_PROHIBITED. */
  return UV_ENOSYS;
#else
  int signal_pipe[2] = { -1, -1 };
  int pipes_storage[8][2];
  int (*pipes)[2];
  int stdio_count;
  ssize_t r;
  pid_t pid;
  int err;
  int exec_errorno;
  int i;
  int status;

  assert(options->file != NULL);
  assert(!(options->flags & ~(UV_PROCESS_DETACHED |
                              UV_PROCESS_SETGID |
                              UV_PROCESS_SETUID |
                              UV_PROCESS_WINDOWS_HIDE |
                              UV_PROCESS_WINDOWS_HIDE_CONSOLE |
                              UV_PROCESS_WINDOWS_HIDE_GUI |
                              UV_PROCESS_WINDOWS_VERBATIM_ARGUMENTS)));

  uv__handle_init(loop, (uv_handle_t*)process, UV_PROCESS);
  QUEUE_INIT(&process->queue);

  stdio_count = options->stdio_count;
  if (stdio_count < 3)
    stdio_count = 3;

  err = UV_ENOMEM;
  pipes = pipes_storage;
  if (stdio_count > (int) ARRAY_SIZE(pipes_storage))
    pipes = uv__malloc(stdio_count * sizeof(*pipes));

  if (pipes == NULL)
    goto error;

  for (i = 0; i < stdio_count; i++) {
    pipes[i][0] = -1;
    pipes[i][1] = -1;
  }

  for (i = 0; i < options->stdio_count; i++) {
    err = uv__process_init_stdio(options->stdio + i, pipes[i]);
    if (err)
      goto error;
  }

  /* This pipe is used by the parent to wait until
   * the child has called `execve()`. We need this
   * to avoid the following race condition:
   *
   *    if ((pid = fork()) > 0) {
   *      kill(pid, SIGTERM);
   *    }
   *    else if (pid == 0) {
   *      execve("/bin/cat", argp, envp);
   *    }
   *
   * The parent sends a signal immediately after forking.
   * Since the child may not have called `execve()` yet,
   * there is no telling what process receives the signal,
   * our fork or /bin/cat.
   *
   * To avoid ambiguity, we create a pipe with both ends
   * marked close-on-exec. Then, after the call to `fork()`,
   * the parent polls the read end until it EOFs or errors with EPIPE.
   */
  err = uv__make_pipe(signal_pipe, 0);
  if (err)
    goto error;

  uv_signal_start(&loop->child_watcher, uv__chld, SIGCHLD);

  /* Acquire write lock to prevent opening new fds in worker threads */
  uv_rwlock_wrlock(&loop->cloexec_lock);
  pid = fork();

  if (pid == -1) {
    err = UV__ERR(errno);
    uv_rwlock_wrunlock(&loop->cloexec_lock);
    uv__close(signal_pipe[0]);
    uv__close(signal_pipe[1]);
    goto error;
  }

  if (pid == 0) {
    uv__process_child_init(options, stdio_count, pipes, signal_pipe[1]);
    abort();
  }

  /* Release lock in parent process */
  uv_rwlock_wrunlock(&loop->cloexec_lock);
  uv__close(signal_pipe[1]);

  process->status = 0;
  exec_errorno = 0;
  do
    r = read(signal_pipe[0], &exec_errorno, sizeof(exec_errorno));
  while (r == -1 && errno == EINTR);

  if (r == 0)
    ; /* okay, EOF */
  else if (r == sizeof(exec_errorno)) {
    do
      err = waitpid(pid, &status, 0); /* okay, read errorno */
    while (err == -1 && errno == EINTR);
    assert(err == pid);
  } else if (r == -1 && errno == EPIPE) {
    do
      err = waitpid(pid, &status, 0); /* okay, got EPIPE */
    while (err == -1 && errno == EINTR);
    assert(err == pid);
  } else
    abort();

  uv__close_nocheckstdio(signal_pipe[0]);

  for (i = 0; i < options->stdio_count; i++) {
    err = uv__process_open_stream(options->stdio + i, pipes[i]);
    if (err == 0)
      continue;

    while (i--)
      uv__process_close_stream(options->stdio + i);

    goto error;
  }

  /* Only activate this handle if exec() happened successfully */
  if (exec_errorno == 0) {
    QUEUE_INSERT_TAIL(&loop->process_handles, &process->queue);
    uv__handle_start(process);
  }

  process->pid = pid;
  process->exit_cb = options->exit_cb;

  if (pipes != pipes_storage)
    uv__free(pipes);

  return exec_errorno;

error:
  if (pipes != NULL) {
    for (i = 0; i < stdio_count; i++) {
      if (i < options->stdio_count)
        if (options->stdio[i].flags & (UV_INHERIT_FD | UV_INHERIT_STREAM))
          continue;
      if (pipes[i][0] != -1)
        uv__close_nocheckstdio(pipes[i][0]);
      if (pipes[i][1] != -1)
        uv__close_nocheckstdio(pipes[i][1]);
    }

    if (pipes != pipes_storage)
      uv__free(pipes);
  }

  return err;
#endif
}