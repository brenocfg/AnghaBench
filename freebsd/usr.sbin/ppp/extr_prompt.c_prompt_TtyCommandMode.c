#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct termios {int c_lflag; int /*<<< orphan*/  c_oflag; int /*<<< orphan*/  c_iflag; } ;
struct TYPE_2__ {int /*<<< orphan*/  c_iflag; } ;
struct prompt {int /*<<< orphan*/ * TermMode; int /*<<< orphan*/  fd_in; TYPE_1__ oldtio; } ;

/* Variables and functions */
 int ECHO ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int ICANON ; 
 int ISIG ; 
 int /*<<< orphan*/  OPOST ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  TCSADRAIN ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 

void
prompt_TtyCommandMode(struct prompt *p)
{
  struct termios newtio;
  int stat;

  tcgetattr(p->fd_in, &newtio);
  newtio.c_lflag |= (ECHO | ISIG | ICANON);
  newtio.c_iflag = p->oldtio.c_iflag;
  newtio.c_oflag |= OPOST;
  tcsetattr(p->fd_in, TCSADRAIN, &newtio);

  stat = fcntl(p->fd_in, F_GETFL, 0);
  if (stat > 0) {
    stat |= O_NONBLOCK;
    fcntl(p->fd_in, F_SETFL, stat);
  }

  p->TermMode = NULL;
}