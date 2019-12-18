#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* full; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {char* devlist; int ndev; } ;
struct physical {int fd; scalar_t__ type; TYPE_3__ name; TYPE_2__ link; int /*<<< orphan*/ * handler; TYPE_1__ cfg; } ;
struct TYPE_8__ {int /*<<< orphan*/ * (* create ) (struct physical*) ;} ;

/* Variables and functions */
 int ID0open (char*,int) ; 
 int /*<<< orphan*/  LogDEBUG ; 
 int /*<<< orphan*/  LogWARN ; 
 unsigned int NDEVICES ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int /*<<< orphan*/  PHYSICAL_NOFORCE ; 
 scalar_t__ PHYS_DIRECT ; 
 int STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 TYPE_4__* devices ; 
 int errno ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  physical_Found (struct physical*) ; 
 scalar_t__ physical_Lock (struct physical*) ; 
 int /*<<< orphan*/  physical_SetDevice (struct physical*,char*) ; 
 int /*<<< orphan*/  physical_SetupStack (struct physical*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  physical_Unlock (struct physical*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/ * stub1 (struct physical*) ; 
 int /*<<< orphan*/ * stub2 (struct physical*) ; 

int
physical_Open(struct physical *p)
{
  char *dev;
  int devno, wasfd, err;
  unsigned h;

  if (p->fd >= 0)
    log_Printf(LogDEBUG, "%s: Open: Modem is already open!\n", p->link.name);
    /* We're going back into "term" mode */
  else if (p->type == PHYS_DIRECT) {
    physical_SetDevice(p, "");
    p->fd = STDIN_FILENO;
    for (h = 0; h < NDEVICES && p->handler == NULL && p->fd >= 0; h++)
      p->handler = (*devices[h].create)(p);
    close(STDOUT_FILENO);
    if (p->fd >= 0) {
      if (p->handler == NULL) {
        physical_SetupStack(p, "unknown", PHYSICAL_NOFORCE);
        log_Printf(LogDEBUG, "%s: stdin is unidentified\n", p->link.name);
      }
      physical_Found(p);
    }
  } else {
    dev = p->cfg.devlist;
    devno = 0;
    while (devno < p->cfg.ndev && p->fd < 0) {
      physical_SetDevice(p, dev);
      if (physical_Lock(p)) {
        err = 0;

        if (*p->name.full == '/') {
          p->fd = ID0open(p->name.full, O_RDWR | O_NONBLOCK);
          if (p->fd < 0)
            err = errno;
        }

        wasfd = p->fd;
        for (h = 0; h < NDEVICES && p->handler == NULL; h++)
          if ((p->handler = (*devices[h].create)(p)) == NULL && wasfd != p->fd)
            break;

        if (p->fd < 0) {
          if (h == NDEVICES) {
            if (err)
	      log_Printf(LogWARN, "%s: %s: %s\n", p->link.name, p->name.full,
                         strerror(errno));
            else
	      log_Printf(LogWARN, "%s: Device (%s) must begin with a '/',"
                         " a '!' or contain at least one ':'\n", p->link.name,
                         p->name.full);
          }
          physical_Unlock(p);
        } else
          physical_Found(p);
      }
      dev += strlen(dev) + 1;
      devno++;
    }
  }

  return p->fd;
}