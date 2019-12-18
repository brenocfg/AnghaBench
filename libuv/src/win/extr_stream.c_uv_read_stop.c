#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_tty_t ;
struct TYPE_4__ {int flags; scalar_t__ type; int /*<<< orphan*/  loop; } ;
typedef  TYPE_1__ uv_stream_t ;
typedef  int /*<<< orphan*/  uv_pipe_t ;

/* Variables and functions */
 int /*<<< orphan*/  DECREASE_ACTIVE_COUNT (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int UV_HANDLE_READING ; 
 scalar_t__ UV_NAMED_PIPE ; 
 scalar_t__ UV_TTY ; 
 int /*<<< orphan*/  uv__pipe_read_stop (int /*<<< orphan*/ *) ; 
 int uv_translate_sys_error (int) ; 
 int uv_tty_read_stop (int /*<<< orphan*/ *) ; 

int uv_read_stop(uv_stream_t* handle) {
  int err;

  if (!(handle->flags & UV_HANDLE_READING))
    return 0;

  err = 0;
  if (handle->type == UV_TTY) {
    err = uv_tty_read_stop((uv_tty_t*) handle);
  } else if (handle->type == UV_NAMED_PIPE) {
    uv__pipe_read_stop((uv_pipe_t*) handle);
  } else {
    handle->flags &= ~UV_HANDLE_READING;
    DECREASE_ACTIVE_COUNT(handle->loop, handle);
  }

  return uv_translate_sys_error(err);
}