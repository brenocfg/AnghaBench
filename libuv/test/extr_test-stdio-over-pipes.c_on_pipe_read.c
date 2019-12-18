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
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ uv_buf_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  close_cb ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  on_pipe_read_called ; 
 int /*<<< orphan*/  stdin_pipe ; 
 int /*<<< orphan*/  stdout_pipe ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on_pipe_read(uv_stream_t* tcp, ssize_t nread, const uv_buf_t* buf) {
  ASSERT(nread > 0);
  ASSERT(memcmp("hello world\n", buf->base, nread) == 0);
  on_pipe_read_called++;

  free(buf->base);

  uv_close((uv_handle_t*)&stdin_pipe, close_cb);
  uv_close((uv_handle_t*)&stdout_pipe, close_cb);
}