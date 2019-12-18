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
struct ttydevice {int /*<<< orphan*/  mbits; int /*<<< orphan*/  Timer; } ;
struct termios {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct physical {scalar_t__ fd; TYPE_1__ link; int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  B0 ; 
 int /*<<< orphan*/  LogWARN ; 
 scalar_t__ Online (struct ttydevice*) ; 
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  TIOCM_DTR ; 
 int cfsetspeed (struct termios*,int /*<<< orphan*/ ) ; 
 struct ttydevice* device2tty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcgetattr (scalar_t__,struct termios*) ; 
 int tcsetattr (scalar_t__,int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  timer_Stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tty_Offline(struct physical *p)
{
  struct ttydevice *dev = device2tty(p->handler);

  if (p->fd >= 0) {
    timer_Stop(&dev->Timer);
    dev->mbits &= ~TIOCM_DTR;	/* XXX: Hmm, what's this supposed to do ? */
    if (Online(dev)) {
      struct termios tio;

      tcgetattr(p->fd, &tio);
      if (cfsetspeed(&tio, B0) == -1 || tcsetattr(p->fd, TCSANOW, &tio) == -1)
        log_Printf(LogWARN, "%s: Unable to set physical to speed 0\n",
                   p->link.name);
    }
  }
}