#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ttydevice {int /*<<< orphan*/  mbits; } ;
struct termios {int c_cflag; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {scalar_t__ rts_cts; } ;
struct physical {scalar_t__ type; scalar_t__ fd; TYPE_2__ link; TYPE_1__ cfg; int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int CCTS_OFLOW ; 
 int CLOCAL ; 
 int CRTS_IFLOW ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int HUPCL ; 
 int /*<<< orphan*/  LoadLineDiscipline (struct physical*) ; 
 int /*<<< orphan*/  LogDEBUG ; 
 int /*<<< orphan*/  LogWARN ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  Online (struct ttydevice*) ; 
 scalar_t__ PHYS_DEDICATED ; 
 scalar_t__ PHYS_DIRECT ; 
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  cfmakeraw (struct termios*) ; 
 struct ttydevice* device2tty (int /*<<< orphan*/ ) ; 
 int fcntl (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  physical_IsSync (struct physical*) ; 
 int /*<<< orphan*/  tcgetattr (scalar_t__,struct termios*) ; 
 int tcsetattr (scalar_t__,int /*<<< orphan*/ ,struct termios*) ; 

__attribute__((used)) static int
tty_Raw(struct physical *p)
{
  struct ttydevice *dev = device2tty(p->handler);
  struct termios ios;
  int oldflag;

  log_Printf(LogDEBUG, "%s: Entering tty_Raw\n", p->link.name);

  if (p->type != PHYS_DIRECT && p->fd >= 0 && !Online(dev))
    log_Printf(LogDEBUG, "%s: Raw: descriptor = %d, mbits = %x\n",
              p->link.name, p->fd, dev->mbits);

  if (!physical_IsSync(p)) {
#ifndef NONETGRAPH
    if (!LoadLineDiscipline(p))
#endif
    {
      tcgetattr(p->fd, &ios);
      cfmakeraw(&ios);
      if (p->cfg.rts_cts)
        ios.c_cflag |= CLOCAL | CCTS_OFLOW | CRTS_IFLOW;
      else
        ios.c_cflag |= CLOCAL;

      if (p->type != PHYS_DEDICATED)
        ios.c_cflag |= HUPCL;

      if (tcsetattr(p->fd, TCSANOW, &ios) == -1)
        log_Printf(LogWARN, "%s: tcsetattr: Failed configuring device\n",
                   p->link.name);
    }
  }

  oldflag = fcntl(p->fd, F_GETFL, 0);
  if (oldflag < 0)
    return 0;
  fcntl(p->fd, F_SETFL, oldflag | O_NONBLOCK);

  return 1;
}