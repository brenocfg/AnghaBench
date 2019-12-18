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
struct termios {int c_lflag; int* c_cc; int /*<<< orphan*/  c_cflag; int /*<<< orphan*/  c_oflag; scalar_t__ c_iflag; } ;
struct prompt {int fd_in; struct termios comtio; struct termios oldtio; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS8 ; 
 int ECHO ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int ICANON ; 
 int ISIG ; 
 int /*<<< orphan*/  OPOST ; 
 int O_NONBLOCK ; 
 int STDIN_FILENO ; 
 int /*<<< orphan*/  TCSANOW ; 
 size_t VINTR ; 
 size_t VMIN ; 
 size_t VTIME ; 
 int _POSIX_VDISABLE ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcgetattr (int,struct termios*) ; 
 int /*<<< orphan*/  tcsetattr (int,int /*<<< orphan*/ ,struct termios*) ; 

void
prompt_TtyInit(struct prompt *p)
{
  int stat, fd = p ? p->fd_in : STDIN_FILENO;
  struct termios newtio;

  stat = fcntl(fd, F_GETFL, 0);
  if (stat > 0) {
    stat |= O_NONBLOCK;
    fcntl(fd, F_SETFL, stat);
  }

  if (p)
    newtio = p->oldtio;
  else
    tcgetattr(fd, &newtio);

  newtio.c_lflag &= ~(ECHO | ISIG | ICANON);
  newtio.c_iflag = 0;
  newtio.c_oflag &= ~OPOST;
  if (!p)
    newtio.c_cc[VINTR] = _POSIX_VDISABLE;
  newtio.c_cc[VMIN] = 1;
  newtio.c_cc[VTIME] = 0;
  newtio.c_cflag |= CS8;
  tcsetattr(fd, TCSANOW, &newtio);
  if (p)
    p->comtio = newtio;
}