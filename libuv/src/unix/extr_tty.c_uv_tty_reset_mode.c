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

/* Variables and functions */
 int /*<<< orphan*/  TCSANOW ; 
 int UV_EBUSY ; 
 int UV__ERR (int) ; 
 int errno ; 
 int /*<<< orphan*/  orig_termios ; 
 int orig_termios_fd ; 
 scalar_t__ tcsetattr (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  termios_spinlock ; 
 int /*<<< orphan*/  uv_spinlock_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_spinlock_unlock (int /*<<< orphan*/ *) ; 

int uv_tty_reset_mode(void) {
  int saved_errno;
  int err;

  saved_errno = errno;
  if (!uv_spinlock_trylock(&termios_spinlock))
    return UV_EBUSY;  /* In uv_tty_set_mode(). */

  err = 0;
  if (orig_termios_fd != -1)
    if (tcsetattr(orig_termios_fd, TCSANOW, &orig_termios))
      err = UV__ERR(errno);

  uv_spinlock_unlock(&termios_spinlock);
  errno = saved_errno;

  return err;
}