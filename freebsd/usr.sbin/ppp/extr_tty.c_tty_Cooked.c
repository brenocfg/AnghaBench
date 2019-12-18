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
struct ttydevice {int /*<<< orphan*/  ios; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct physical {int /*<<< orphan*/  fd; TYPE_1__ link; int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  LogWARN ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  TCIOFLUSH ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 int /*<<< orphan*/  UnloadLineDiscipline (struct physical*) ; 
 struct ttydevice* device2tty (int /*<<< orphan*/ ) ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  physical_IsSync (struct physical*) ; 
 int /*<<< orphan*/  tcflush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_Offline (struct physical*) ; 

__attribute__((used)) static void
tty_Cooked(struct physical *p)
{
  struct ttydevice *dev = device2tty(p->handler);
  int oldflag;

  tty_Offline(p);	/* In case of emergency close()s */

  tcflush(p->fd, TCIOFLUSH);

  if (!physical_IsSync(p) && tcsetattr(p->fd, TCSAFLUSH, &dev->ios) == -1)
    log_Printf(LogWARN, "%s: tcsetattr: Unable to restore device settings\n",
               p->link.name);

#ifndef NONETGRAPH
  UnloadLineDiscipline(p);
#endif

  if ((oldflag = fcntl(p->fd, F_GETFL, 0)) != -1)
    fcntl(p->fd, F_SETFL, oldflag & ~O_NONBLOCK);
}