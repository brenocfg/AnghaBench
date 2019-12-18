#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_stream_t ;
struct TYPE_7__ {int /*<<< orphan*/  loop; } ;
typedef  TYPE_1__ uv_pipe_t ;
typedef  scalar_t__ uv_handle_type ;
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ UV_NAMED_PIPE ; 
 int /*<<< orphan*/  close_cb ; 
 TYPE_1__* incoming ; 
 unsigned int incoming_count ; 
 scalar_t__ uv_accept (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_pipe_init (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_pipe_pending_count (TYPE_1__*) ; 
 scalar_t__ uv_pipe_pending_type (TYPE_1__*) ; 
 scalar_t__ uv_read_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void read_cb(uv_stream_t* handle,
                    ssize_t nread,
                    const uv_buf_t* buf) {
  uv_pipe_t* p;
  uv_pipe_t* inc;
  uv_handle_type pending;
  unsigned int i;

  p = (uv_pipe_t*) handle;
  ASSERT(nread >= 0);

  while (uv_pipe_pending_count(p) != 0) {
    pending = uv_pipe_pending_type(p);
    ASSERT(pending == UV_NAMED_PIPE);

    ASSERT(incoming_count < ARRAY_SIZE(incoming));
    inc = &incoming[incoming_count++];
    ASSERT(0 == uv_pipe_init(p->loop, inc, 0));
    ASSERT(0 == uv_accept(handle, (uv_stream_t*) inc));
  }

  if (incoming_count != ARRAY_SIZE(incoming))
    return;

  ASSERT(0 == uv_read_stop((uv_stream_t*) p));
  uv_close((uv_handle_t*) p, close_cb);
  for (i = 0; i < ARRAY_SIZE(incoming); i++)
    uv_close((uv_handle_t*) &incoming[i], close_cb);
}