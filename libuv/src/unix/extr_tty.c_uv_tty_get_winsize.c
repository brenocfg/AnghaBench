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
typedef  int /*<<< orphan*/  uv_tty_t ;
struct winsize {int ws_col; int ws_row; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int UV__ERR (scalar_t__) ; 
 scalar_t__ errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct winsize*) ; 
 int /*<<< orphan*/  uv__stream_fd (int /*<<< orphan*/ *) ; 

int uv_tty_get_winsize(uv_tty_t* tty, int* width, int* height) {
  struct winsize ws;
  int err;

  do
    err = ioctl(uv__stream_fd(tty), TIOCGWINSZ, &ws);
  while (err == -1 && errno == EINTR);

  if (err == -1)
    return UV__ERR(errno);

  *width = ws.ws_col;
  *height = ws.ws_row;

  return 0;
}