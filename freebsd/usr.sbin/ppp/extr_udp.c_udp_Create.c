#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  name; } ;
struct udpdevice {struct device dev; int /*<<< orphan*/  connected; } ;
struct stat {int st_mode; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct TYPE_11__ {scalar_t__ necessity; } ;
struct TYPE_12__ {TYPE_5__ cd; } ;
struct TYPE_8__ {scalar_t__ openmode; } ;
struct TYPE_9__ {TYPE_2__ cfg; } ;
struct TYPE_10__ {TYPE_3__ lcp; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {char* full; } ;
struct physical {int fd; TYPE_6__ cfg; TYPE_4__ link; TYPE_1__ name; } ;

/* Variables and functions */
 scalar_t__ CD_DEFAULT ; 
 int /*<<< orphan*/  LogPHASE ; 
 int /*<<< orphan*/  LogWARN ; 
 scalar_t__ OPEN_PASSIVE ; 
 int /*<<< orphan*/  PHYSICAL_FORCE_SYNC ; 
 int SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_TYPE ; 
 int S_IFSOCK ; 
 int /*<<< orphan*/  UDP_CONNECTED ; 
 int /*<<< orphan*/  UDP_MAYBEUNCONNECTED ; 
 int /*<<< orphan*/  baseudpdevice ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int fstat (int,struct stat*) ; 
 scalar_t__ getpeername (int,struct sockaddr*,int*) ; 
 int getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,...) ; 
 struct udpdevice* malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  physical_SetupStack (struct physical*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 struct udpdevice* udp_CreateDevice (struct physical*,char*,char*) ; 

struct device *
udp_Create(struct physical *p)
{
  char *cp, *host, *port, *svc;
  struct udpdevice *dev;

  dev = NULL;
  if (p->fd < 0) {
    if ((cp = strchr(p->name.full, ':')) != NULL && !strchr(cp + 1, ':')) {
      *cp = '\0';
      host = p->name.full;
      port = cp + 1;
      svc = strchr(port, '/');
      if (svc && strcasecmp(svc, "/udp")) {
        *cp = ':';
        return NULL;
      }
      if (svc) {
        p->fd--;     /* We own the device but maybe can't use it - change fd */
        *svc = '\0';
      }

      if (*host && *port)
        dev = udp_CreateDevice(p, host, port);

      *cp = ':';
      if (svc)
        *svc = '/';
    }
  } else {
    /* See if we're a connected udp socket */
    struct stat st;

    if (fstat(p->fd, &st) != -1 && (st.st_mode & S_IFSOCK)) {
      int type, sz;

      sz = sizeof type;
      if (getsockopt(p->fd, SOL_SOCKET, SO_TYPE, &type, &sz) == -1) {
        log_Printf(LogPHASE, "%s: Link is a closed socket !\n", p->link.name);
        close(p->fd);
        p->fd = -1;
        return NULL;
      }

      if (sz == sizeof type && type == SOCK_DGRAM) {
        struct sockaddr_in sock;
        struct sockaddr *sockp = (struct sockaddr *)&sock;

        if ((dev = malloc(sizeof *dev)) == NULL) {
          log_Printf(LogWARN, "%s: Cannot allocate a udp device: %s\n",
                     p->link.name, strerror(errno));
          return NULL;
        }

        if (getpeername(p->fd, sockp, &sz) == 0) {
          log_Printf(LogPHASE, "%s: Link is a connected udp socket\n",
                     p->link.name);
          dev->connected = UDP_CONNECTED;
	} else {
          log_Printf(LogPHASE, "%s: Link is a disconnected udp socket\n",
                     p->link.name);

          dev->connected = UDP_MAYBEUNCONNECTED;

          if (p->link.lcp.cfg.openmode != OPEN_PASSIVE) {
            log_Printf(LogPHASE, "%s:   Changing openmode to PASSIVE\n",
                       p->link.name);
            p->link.lcp.cfg.openmode = OPEN_PASSIVE;
          }
        }
      }
    }
  }

  if (dev) {
    memcpy(&dev->dev, &baseudpdevice, sizeof dev->dev);
    physical_SetupStack(p, dev->dev.name, PHYSICAL_FORCE_SYNC);
    if (p->cfg.cd.necessity != CD_DEFAULT)
      log_Printf(LogWARN, "Carrier settings ignored\n");
    return &dev->dev;
  }

  return NULL;
}