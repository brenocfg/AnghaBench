#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  load; } ;
struct TYPE_12__ {scalar_t__ delay; scalar_t__ necessity; } ;
struct TYPE_13__ {TYPE_4__ cd; } ;
struct ttydevice {int mbits; scalar_t__ carrier_seconds; TYPE_7__ Timer; TYPE_5__ dev; } ;
struct TYPE_14__ {int /*<<< orphan*/  name; } ;
struct TYPE_11__ {char* full; } ;
struct TYPE_9__ {scalar_t__ necessity; } ;
struct TYPE_10__ {TYPE_1__ cd; } ;
struct physical {scalar_t__ fd; TYPE_6__ link; int /*<<< orphan*/  dl; TYPE_3__ name; TYPE_2__ cfg; int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 scalar_t__ CD_DEFAULT ; 
 scalar_t__ CD_REQUIRED ; 
 int /*<<< orphan*/  CLOSE_NORMAL ; 
 int /*<<< orphan*/  LogDEBUG ; 
 int /*<<< orphan*/  LogPHASE ; 
 int /*<<< orphan*/  LogWARN ; 
 scalar_t__ Online (struct ttydevice*) ; 
 int /*<<< orphan*/  SECTICKS ; 
 int /*<<< orphan*/  TIOCMGET ; 
 int TIOCM_CD ; 
 int /*<<< orphan*/  datalink_Down (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ttydevice* device2tty (int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  timer_Start (TYPE_7__*) ; 
 int /*<<< orphan*/  timer_Stop (TYPE_7__*) ; 

__attribute__((used)) static void
tty_Timeout(void *data)
{
  struct physical *p = data;
  struct ttydevice *dev = device2tty(p->handler);
  int ombits, change;

  timer_Stop(&dev->Timer);
  dev->Timer.load = SECTICKS;		/* Once a second please */
  timer_Start(&dev->Timer);
  ombits = dev->mbits;

  if (p->fd >= 0) {
    if (ioctl(p->fd, TIOCMGET, &dev->mbits) < 0) {
      /* we must be a pty ? */
      if (p->cfg.cd.necessity != CD_DEFAULT)
        log_Printf(LogWARN, "%s: Carrier ioctl not supported, "
                   "using ``set cd off''\n", p->link.name);
      timer_Stop(&dev->Timer);
      dev->mbits = TIOCM_CD;
      return;
    }
  } else
    dev->mbits = 0;

  if (ombits == -1) {
    /* First time looking for carrier */
    if (Online(dev))
      log_Printf(LogPHASE, "%s: %s: CD detected\n", p->link.name, p->name.full);
    else if (++dev->carrier_seconds >= dev->dev.cd.delay) {
      if (dev->dev.cd.necessity == CD_REQUIRED)
        log_Printf(LogPHASE, "%s: %s: Required CD not detected\n",
                   p->link.name, p->name.full);
      else {
        log_Printf(LogPHASE, "%s: %s doesn't support CD\n",
                   p->link.name, p->name.full);
        dev->mbits = TIOCM_CD;		/* Dodgy null-modem cable ? */
      }
      timer_Stop(&dev->Timer);
      /* tty_AwaitCarrier() will notice */
    } else {
      /* Keep waiting */
      log_Printf(LogDEBUG, "%s: %s: Still no carrier (%d/%d)\n",
                 p->link.name, p->name.full, dev->carrier_seconds,
                 dev->dev.cd.delay);
      dev->mbits = -1;
    }
  } else {
    change = ombits ^ dev->mbits;
    if (change & TIOCM_CD) {
      if (dev->mbits & TIOCM_CD)
        log_Printf(LogDEBUG, "%s: offline -> online\n", p->link.name);
      else {
        log_Printf(LogDEBUG, "%s: online -> offline\n", p->link.name);
        log_Printf(LogPHASE, "%s: Carrier lost\n", p->link.name);
        datalink_Down(p->dl, CLOSE_NORMAL);
        timer_Stop(&dev->Timer);
      }
    } else
      log_Printf(LogDEBUG, "%s: Still %sline\n", p->link.name,
                 Online(dev) ? "on" : "off");
  }
}