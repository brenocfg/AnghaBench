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
struct termios {int c_iflag; int c_lflag; int* c_cc; int /*<<< orphan*/  c_cflag; int /*<<< orphan*/  c_oflag; } ;
struct TYPE_4__ {int mode; struct termios orig_termios; } ;
typedef  TYPE_1__ uv_tty_t ;
typedef  int uv_tty_mode_t ;

/* Variables and functions */
 int BRKINT ; 
 int /*<<< orphan*/  CS8 ; 
 int ECHO ; 
 int ICANON ; 
 int ICRNL ; 
 int IEXTEN ; 
 int INPCK ; 
 int ISIG ; 
 int ISTRIP ; 
 int IXON ; 
 int /*<<< orphan*/  ONLCR ; 
 int /*<<< orphan*/  TCSADRAIN ; 
#define  UV_TTY_MODE_IO 130 
#define  UV_TTY_MODE_NORMAL 129 
#define  UV_TTY_MODE_RAW 128 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 size_t VMIN ; 
 size_t VTIME ; 
 int /*<<< orphan*/  errno ; 
 struct termios orig_termios ; 
 int orig_termios_fd ; 
 scalar_t__ tcgetattr (int,struct termios*) ; 
 scalar_t__ tcsetattr (int,int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  termios_spinlock ; 
 int uv__stream_fd (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__tty_make_raw (struct termios*) ; 
 int /*<<< orphan*/  uv_spinlock_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_spinlock_unlock (int /*<<< orphan*/ *) ; 

int uv_tty_set_mode(uv_tty_t* tty, uv_tty_mode_t mode) {
  struct termios tmp;
  int fd;

  if (tty->mode == (int) mode)
    return 0;

  fd = uv__stream_fd(tty);
  if (tty->mode == UV_TTY_MODE_NORMAL && mode != UV_TTY_MODE_NORMAL) {
    if (tcgetattr(fd, &tty->orig_termios))
      return UV__ERR(errno);

    /* This is used for uv_tty_reset_mode() */
    uv_spinlock_lock(&termios_spinlock);
    if (orig_termios_fd == -1) {
      orig_termios = tty->orig_termios;
      orig_termios_fd = fd;
    }
    uv_spinlock_unlock(&termios_spinlock);
  }

  tmp = tty->orig_termios;
  switch (mode) {
    case UV_TTY_MODE_NORMAL:
      break;
    case UV_TTY_MODE_RAW:
      tmp.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
      tmp.c_oflag |= (ONLCR);
      tmp.c_cflag |= (CS8);
      tmp.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
      tmp.c_cc[VMIN] = 1;
      tmp.c_cc[VTIME] = 0;
      break;
    case UV_TTY_MODE_IO:
      uv__tty_make_raw(&tmp);
      break;
  }

  /* Apply changes after draining */
  if (tcsetattr(fd, TCSADRAIN, &tmp))
    return UV__ERR(errno);

  tty->mode = mode;
  return 0;
}