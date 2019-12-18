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
struct TYPE_8__ {scalar_t__ s_addr; } ;
struct TYPE_6__ {scalar_t__ sin_port; TYPE_4__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct udpdevice {int /*<<< orphan*/  connected; TYPE_2__ sock; } ;
struct sockaddr {int dummy; } ;
struct servent {scalar_t__ s_port; } ;
struct TYPE_7__ {char* full; } ;
struct TYPE_5__ {char* name; } ;
struct physical {int fd; TYPE_3__ name; TYPE_1__ link; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 TYPE_4__ GetIpAddr (char*) ; 
 scalar_t__ INADDR_NONE ; 
 int /*<<< orphan*/  LogDEBUG ; 
 int /*<<< orphan*/  LogPHASE ; 
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  UDP_CONNECTED ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct udpdevice*) ; 
 struct servent* getservbyname (char*,char*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,char*,char*,...) ; 
 struct udpdevice* malloc (int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct udpdevice *
udp_CreateDevice(struct physical *p, char *host, char *port)
{
  struct udpdevice *dev;
  struct servent *sp;

  if ((dev = malloc(sizeof *dev)) == NULL) {
    log_Printf(LogWARN, "%s: Cannot allocate a udp device: %s\n",
               p->link.name, strerror(errno));
    return NULL;
  }

  dev->sock.sin_family = AF_INET;
  dev->sock.sin_addr = GetIpAddr(host);
  if (dev->sock.sin_addr.s_addr == INADDR_NONE) {
    log_Printf(LogWARN, "%s: %s: unknown host\n", p->link.name, host);
    free(dev);
    return NULL;
  }
  dev->sock.sin_port = htons(atoi(port));
  if (dev->sock.sin_port == 0) {
    sp = getservbyname(port, "udp");
    if (sp)
      dev->sock.sin_port = sp->s_port;
    else {
      log_Printf(LogWARN, "%s: %s: unknown service\n", p->link.name, port);
      free(dev);
      return NULL;
    }
  }

  log_Printf(LogPHASE, "%s: Connecting to %s:%s/udp\n", p->link.name,
             host, port);

  p->fd = socket(PF_INET, SOCK_DGRAM, 0);
  if (p->fd >= 0) {
    log_Printf(LogDEBUG, "%s: Opened udp socket %s\n", p->link.name,
               p->name.full);
    if (connect(p->fd, (struct sockaddr *)&dev->sock, sizeof dev->sock) == 0) {
      dev->connected = UDP_CONNECTED;
      return dev;
    } else
      log_Printf(LogWARN, "%s: connect: %s\n", p->name.full, strerror(errno));
  } else
    log_Printf(LogWARN, "%s: socket: %s\n", p->name.full, strerror(errno));

  close(p->fd);
  p->fd = -1;
  free(dev);

  return NULL;
}