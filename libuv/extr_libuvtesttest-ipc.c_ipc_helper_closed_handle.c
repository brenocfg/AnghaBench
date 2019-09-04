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
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  LARGE_SIZE ; 
 int /*<<< orphan*/  MAKE_VALGRIND_HAPPY () ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 int /*<<< orphan*/  buffer ; 
 int /*<<< orphan*/  channel ; 
 int closed_handle_write ; 
 int /*<<< orphan*/  large_buf ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_handle_and_close () ; 
 int /*<<< orphan*/  uv_buf_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 scalar_t__ uv_is_closing (int /*<<< orphan*/ *) ; 
 int uv_is_readable (int /*<<< orphan*/ *) ; 
 int uv_is_writable (int /*<<< orphan*/ *) ; 
 int uv_pipe_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uv_pipe_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uv_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ write_until_data_queued () ; 

int ipc_helper_closed_handle(void) {
  int r;

  memset(buffer, '.', LARGE_SIZE);
  large_buf = uv_buf_init(buffer, LARGE_SIZE);

  r = uv_pipe_init(uv_default_loop(), &channel, 1);
  ASSERT(r == 0);

  uv_pipe_open(&channel, 0);

  ASSERT(1 == uv_is_readable((uv_stream_t*) &channel));
  ASSERT(1 == uv_is_writable((uv_stream_t*) &channel));
  ASSERT(0 == uv_is_closing((uv_handle_t*) &channel));

  if (write_until_data_queued() > 0)
    send_handle_and_close();

  r = uv_run(uv_default_loop(), UV_RUN_DEFAULT);
  ASSERT(r == 0);

  ASSERT(closed_handle_write == 1);

  MAKE_VALGRIND_HAPPY();
  return 0;
}