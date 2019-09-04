#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_thread_t ;
typedef  int /*<<< orphan*/  uv_signal_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  char uv_buf_t ;
typedef  int /*<<< orphan*/  test_buf ;
struct thread_ctx {int doread; int interval; int size; char* data; int fd; int /*<<< orphan*/  pid; } ;
struct TYPE_6__ {int result; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  MAKE_VALGRIND_HAPPY () ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int UV_EINTR ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  loop ; 
 void* malloc (int) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  pthread_self () ; 
 TYPE_1__ read_req ; 
 int /*<<< orphan*/  sig_func ; 
 int /*<<< orphan*/  thread_main ; 
 char uv_buf_init (char*,int) ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 int uv_fs_read (int /*<<< orphan*/ ,TYPE_1__*,int,char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (TYPE_1__*) ; 
 int uv_fs_write (int /*<<< orphan*/ ,TYPE_1__*,int,char*,size_t,int,int /*<<< orphan*/ *) ; 
 scalar_t__ uv_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_signal_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ uv_signal_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t uv_test_fs_buf_offset (char*,int) ; 
 scalar_t__ uv_thread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct thread_ctx*) ; 
 scalar_t__ uv_thread_join (int /*<<< orphan*/ *) ; 
 TYPE_1__ write_req ; 

__attribute__((used)) static void test_fs_partial(int doread) {
  struct thread_ctx ctx;
  uv_thread_t thread;
  uv_signal_t signal;
  int pipe_fds[2];
  size_t iovcount;
  uv_buf_t* iovs;
  char* buffer;
  size_t index;

  iovcount = 54321;

  iovs = malloc(sizeof(*iovs) * iovcount);
  ASSERT(iovs != NULL);

  ctx.pid = pthread_self();
  ctx.doread = doread;
  ctx.interval = 1000;
  ctx.size = sizeof(test_buf) * iovcount;
  ctx.data = malloc(ctx.size);
  ASSERT(ctx.data != NULL);
  buffer = malloc(ctx.size);
  ASSERT(buffer != NULL);

  for (index = 0; index < iovcount; ++index)
    iovs[index] = uv_buf_init(buffer + index * sizeof(test_buf), sizeof(test_buf));

  loop = uv_default_loop();

  ASSERT(0 == uv_signal_init(loop, &signal));
  ASSERT(0 == uv_signal_start(&signal, sig_func, SIGUSR1));

  ASSERT(0 == pipe(pipe_fds));

  ctx.fd = pipe_fds[doread];
  ASSERT(0 == uv_thread_create(&thread, thread_main, &ctx));

  if (doread) {
    uv_buf_t* read_iovs;
    int nread;
    read_iovs = iovs;
    nread = 0;
    while (nread < ctx.size) {
      int result;
      result = uv_fs_read(loop, &read_req, pipe_fds[0], read_iovs, iovcount, -1, NULL);
      if (result > 0) {
        size_t read_iovcount;
        read_iovcount = uv_test_fs_buf_offset(read_iovs, result);
        read_iovs += read_iovcount;
        iovcount -= read_iovcount;
        nread += result;
      } else {
        ASSERT(result == UV_EINTR);
      }
      uv_fs_req_cleanup(&read_req);
    }
  } else {
    int result;
    result = uv_fs_write(loop, &write_req, pipe_fds[1], iovs, iovcount, -1, NULL);
    ASSERT(write_req.result == result);
    ASSERT(result == ctx.size);
    uv_fs_req_cleanup(&write_req);
  }

  ASSERT(0 == memcmp(buffer, ctx.data, ctx.size));

  ASSERT(0 == uv_thread_join(&thread));
  ASSERT(0 == uv_run(loop, UV_RUN_DEFAULT));

  ASSERT(0 == close(pipe_fds[1]));
  uv_close((uv_handle_t*) &signal, NULL);

  { /* Make sure we read everything that we wrote. */
      int result;
      result = uv_fs_read(loop, &read_req, pipe_fds[0], iovs, 1, -1, NULL);
      ASSERT(result == 0);
      uv_fs_req_cleanup(&read_req);
  }
  ASSERT(0 == close(pipe_fds[0]));

  free(iovs);
  free(buffer);
  free(ctx.data);

  MAKE_VALGRIND_HAPPY();
}