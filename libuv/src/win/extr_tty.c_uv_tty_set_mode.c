#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; int /*<<< orphan*/  handle; int /*<<< orphan*/ * read_cb; int /*<<< orphan*/ * alloc_cb; } ;
typedef  TYPE_1__ uv_tty_t ;
typedef  int uv_tty_mode_t ;
typedef  int /*<<< orphan*/ * uv_read_cb ;
typedef  int /*<<< orphan*/ * uv_alloc_cb ;
typedef  int DWORD ;

/* Variables and functions */
 int ENABLE_ECHO_INPUT ; 
 int ENABLE_LINE_INPUT ; 
 int ENABLE_PROCESSED_INPUT ; 
 int ENABLE_WINDOW_INPUT ; 
 int GetLastError () ; 
 int /*<<< orphan*/  SetConsoleMode (int /*<<< orphan*/ ,int) ; 
 int UV_EINVAL ; 
 int UV_ENOTSUP ; 
 int UV_HANDLE_READING ; 
 int UV_HANDLE_TTY_RAW ; 
 int UV_HANDLE_TTY_READABLE ; 
#define  UV_TTY_MODE_IO 130 
#define  UV_TTY_MODE_NORMAL 129 
#define  UV_TTY_MODE_RAW 128 
 int /*<<< orphan*/  uv_sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_sem_wait (int /*<<< orphan*/ *) ; 
 int uv_translate_sys_error (int) ; 
 int /*<<< orphan*/  uv_tty_output_lock ; 
 int uv_tty_read_start (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int uv_tty_read_stop (TYPE_1__*) ; 

int uv_tty_set_mode(uv_tty_t* tty, uv_tty_mode_t mode) {
  DWORD flags;
  unsigned char was_reading;
  uv_alloc_cb alloc_cb;
  uv_read_cb read_cb;
  int err;

  if (!(tty->flags & UV_HANDLE_TTY_READABLE)) {
    return UV_EINVAL;
  }

  if (!!mode == !!(tty->flags & UV_HANDLE_TTY_RAW)) {
    return 0;
  }

  switch (mode) {
    case UV_TTY_MODE_NORMAL:
      flags = ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_PROCESSED_INPUT;
      break;
    case UV_TTY_MODE_RAW:
      flags = ENABLE_WINDOW_INPUT;
      break;
    case UV_TTY_MODE_IO:
      return UV_ENOTSUP;
    default:
      return UV_EINVAL;
  }

  /* If currently reading, stop, and restart reading. */
  if (tty->flags & UV_HANDLE_READING) {
    was_reading = 1;
    alloc_cb = tty->alloc_cb;
    read_cb = tty->read_cb;
    err = uv_tty_read_stop(tty);
    if (err) {
      return uv_translate_sys_error(err);
    }
  } else {
    was_reading = 0;
    alloc_cb = NULL;
    read_cb = NULL;
  }

  uv_sem_wait(&uv_tty_output_lock);
  if (!SetConsoleMode(tty->handle, flags)) {
    err = uv_translate_sys_error(GetLastError());
    uv_sem_post(&uv_tty_output_lock);
    return err;
  }
  uv_sem_post(&uv_tty_output_lock);

  /* Update flag. */
  tty->flags &= ~UV_HANDLE_TTY_RAW;
  tty->flags |= mode ? UV_HANDLE_TTY_RAW : 0;

  /* If we just stopped reading, restart. */
  if (was_reading) {
    err = uv_tty_read_start(tty, alloc_cb, read_cb);
    if (err) {
      return uv_translate_sys_error(err);
    }
  }

  return 0;
}