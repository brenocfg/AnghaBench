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
typedef  int /*<<< orphan*/  uv_write_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char**) ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  MAKE_VALGRIND_HAPPY () ; 
 scalar_t__ UV_NAMED_PIPE ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 int /*<<< orphan*/  after_pipe_write ; 
 int after_write_called ; 
 int close_cb_called ; 
 int /*<<< orphan*/  notify_parent_process () ; 
 int /*<<< orphan*/  on_pipe_read ; 
 int on_pipe_read_called ; 
 int /*<<< orphan*/  on_read_alloc ; 
 int /*<<< orphan*/  stdin_pipe ; 
 int /*<<< orphan*/  stdout_pipe ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  uv_buf_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uv_default_loop () ; 
 scalar_t__ uv_guess_handle (int) ; 
 int uv_pipe_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_pipe_open (int /*<<< orphan*/ *,int) ; 
 int uv_read_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_run (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_unref (int /*<<< orphan*/ *) ; 
 int uv_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int stdio_over_pipes_helper(void) {
  /* Write several buffers to test that the write order is preserved. */
  char* buffers[] = {
    "he",
    "ll",
    "o ",
    "wo",
    "rl",
    "d",
    "\n"
  };

  uv_write_t write_req[ARRAY_SIZE(buffers)];
  uv_buf_t buf[ARRAY_SIZE(buffers)];
  unsigned int i;
  int r;
  uv_loop_t* loop = uv_default_loop();

  ASSERT(UV_NAMED_PIPE == uv_guess_handle(0));
  ASSERT(UV_NAMED_PIPE == uv_guess_handle(1));

  r = uv_pipe_init(loop, &stdin_pipe, 0);
  ASSERT(r == 0);
  r = uv_pipe_init(loop, &stdout_pipe, 0);
  ASSERT(r == 0);

  uv_pipe_open(&stdin_pipe, 0);
  uv_pipe_open(&stdout_pipe, 1);

  /* Unref both stdio handles to make sure that all writes complete. */
  uv_unref((uv_handle_t*)&stdin_pipe);
  uv_unref((uv_handle_t*)&stdout_pipe);

  for (i = 0; i < ARRAY_SIZE(buffers); i++) {
    buf[i] = uv_buf_init((char*)buffers[i], strlen(buffers[i]));
  }

  for (i = 0; i < ARRAY_SIZE(buffers); i++) {
    r = uv_write(&write_req[i], (uv_stream_t*)&stdout_pipe, &buf[i], 1,
      after_pipe_write);
    ASSERT(r == 0);
  }

  notify_parent_process();
  uv_run(loop, UV_RUN_DEFAULT);

  ASSERT(after_write_called == 7);
  ASSERT(on_pipe_read_called == 0);
  ASSERT(close_cb_called == 0);

  uv_ref((uv_handle_t*)&stdout_pipe);
  uv_ref((uv_handle_t*)&stdin_pipe);

  r = uv_read_start((uv_stream_t*)&stdin_pipe, on_read_alloc, on_pipe_read);
  ASSERT(r == 0);

  uv_run(loop, UV_RUN_DEFAULT);

  ASSERT(after_write_called == 7);
  ASSERT(on_pipe_read_called == 1);
  ASSERT(close_cb_called == 2);

  MAKE_VALGRIND_HAPPY();
  return 0;
}