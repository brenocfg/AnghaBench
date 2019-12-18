#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_7__ {scalar_t__ necessity; } ;
struct device {int /*<<< orphan*/  name; TYPE_2__ cd; } ;
struct termios {int c_cflag; scalar_t__ c_oflag; scalar_t__ c_iflag; } ;
struct TYPE_6__ {int fd; int disc; scalar_t__ speed; } ;
struct ttydevice {int mbits; char* hook; struct device dev; struct termios ios; TYPE_1__ real; int /*<<< orphan*/  Timer; } ;
struct TYPE_10__ {int name; } ;
struct TYPE_9__ {int parity; int speed; scalar_t__ rts_cts; TYPE_2__ cd; } ;
struct TYPE_8__ {char* full; } ;
struct physical {int fd; scalar_t__ type; TYPE_5__ link; TYPE_4__ cfg; TYPE_3__ name; } ;

/* Variables and functions */
 int CCTS_OFLOW ; 
 scalar_t__ CD_DEFAULT ; 
 int CLOCAL ; 
 int CRTS_IFLOW ; 
 int CSIZE ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int HUPCL ; 
 scalar_t__ IXOFF ; 
 scalar_t__ IXON ; 
 int /*<<< orphan*/  LogDEBUG ; 
 int /*<<< orphan*/  LogWARN ; 
 int O_NONBLOCK ; 
 int PARENB ; 
 int PARODD ; 
 int /*<<< orphan*/  PHYSICAL_NOFORCE ; 
 scalar_t__ PHYS_DEDICATED ; 
 scalar_t__ PHYS_DIRECT ; 
 int /*<<< orphan*/  TCSADRAIN ; 
 int /*<<< orphan*/  UnsignedToSpeed (int) ; 
 int /*<<< orphan*/  basettydevice ; 
 int /*<<< orphan*/  cfmakeraw (struct termios*) ; 
 int cfsetspeed (struct termios*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (struct ttydevice*) ; 
 int /*<<< orphan*/  isatty (int) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int,...) ; 
 struct ttydevice* malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/  physical_SetDevice (struct physical*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  physical_SetupStack (struct physical*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int) ; 
 int /*<<< orphan*/  tcgetattr (int,struct termios*) ; 
 int tcsetattr (int,int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  tty_Cooked (struct physical*) ; 
 int /*<<< orphan*/  ttyname (int) ; 

struct device *
tty_Create(struct physical *p)
{
  struct ttydevice *dev;
  struct termios ios;
  int oldflag;

  if (p->fd < 0 || !isatty(p->fd))
    /* Don't want this */
    return NULL;

  if (*p->name.full == '\0') {
    physical_SetDevice(p, ttyname(p->fd));
    log_Printf(LogDEBUG, "%s: Input is a tty (%s)\n",
               p->link.name, p->name.full);
  } else
    log_Printf(LogDEBUG, "%s: Opened %s\n", p->link.name, p->name.full);

  /* We're gonna return a ttydevice (unless something goes horribly wrong) */

  if ((dev = malloc(sizeof *dev)) == NULL) {
    /* Complete failure - parent doesn't continue trying to ``create'' */
    close(p->fd);
    p->fd = -1;
    return NULL;
  }

  memcpy(&dev->dev, &basettydevice, sizeof dev->dev);
  memset(&dev->Timer, '\0', sizeof dev->Timer);
  dev->mbits = -1;
#ifndef NONETGRAPH
  dev->real.speed = 0;
  dev->real.fd = -1;
  dev->real.disc = -1;
  *dev->hook = '\0';
#endif
  tcgetattr(p->fd, &ios);
  dev->ios = ios;

  if (p->cfg.cd.necessity != CD_DEFAULT)
    /* Any override is ok for the tty device */
    dev->dev.cd = p->cfg.cd;

  log_Printf(LogDEBUG, "%s: tty_Create: physical (get): fd = %d,"
             " iflag = %lx, oflag = %lx, cflag = %lx\n", p->link.name, p->fd,
             (u_long)ios.c_iflag, (u_long)ios.c_oflag, (u_long)ios.c_cflag);

  cfmakeraw(&ios);
  if (p->cfg.rts_cts)
    ios.c_cflag |= CLOCAL | CCTS_OFLOW | CRTS_IFLOW;
  else {
    ios.c_cflag |= CLOCAL;
    ios.c_iflag |= IXOFF;
  }
  ios.c_iflag |= IXON;
  if (p->type != PHYS_DEDICATED)
    ios.c_cflag |= HUPCL;

  if (p->type != PHYS_DIRECT) {
      /* Change tty speed when we're not in -direct mode */
      ios.c_cflag &= ~(CSIZE | PARODD | PARENB);
      ios.c_cflag |= p->cfg.parity;
      if (cfsetspeed(&ios, UnsignedToSpeed(p->cfg.speed)) == -1)
	log_Printf(LogWARN, "%s: %s: Unable to set speed to %d\n",
		  p->link.name, p->name.full, p->cfg.speed);
  }

  if (tcsetattr(p->fd, TCSADRAIN, &ios) == -1) {
    log_Printf(LogWARN, "%s: tcsetattr: Failed configuring device\n",
               p->link.name);
    if (p->type != PHYS_DIRECT && p->cfg.speed > 115200)
      log_Printf(LogWARN, "%.*s             Perhaps the speed is unsupported\n",
                 (int)strlen(p->link.name), "");
  }

  log_Printf(LogDEBUG, "%s: physical (put): iflag = %lx, oflag = %lx, "
            "cflag = %lx\n", p->link.name, (u_long)ios.c_iflag,
            (u_long)ios.c_oflag, (u_long)ios.c_cflag);

  oldflag = fcntl(p->fd, F_GETFL, 0);
  if (oldflag < 0) {
    /* Complete failure - parent doesn't continue trying to ``create'' */

    log_Printf(LogWARN, "%s: Open: Cannot get physical flags: %s\n",
               p->link.name, strerror(errno));
    tty_Cooked(p);
    close(p->fd);
    p->fd = -1;
    free(dev);
    return NULL;
  } else
    fcntl(p->fd, F_SETFL, oldflag & ~O_NONBLOCK);

  physical_SetupStack(p, dev->dev.name, PHYSICAL_NOFORCE);

  return &dev->dev;
}