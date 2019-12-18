#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct sockaddr {int dummy; } ;
struct TYPE_4__ {int class; int len; scalar_t__ address; } ;
struct peerid {char* authname; TYPE_1__ enddisc; } ;
struct TYPE_5__ {int sun_len; int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct mpserver {int fd; TYPE_2__ socket; } ;
typedef  int mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LOCAL ; 
 scalar_t__ EADDRINUSE ; 
 scalar_t__ ECONNREFUSED ; 
 scalar_t__ ID0bind_un (int,TYPE_2__*) ; 
 scalar_t__ ID0connect_un (int,TYPE_2__*) ; 
 int ID0socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LogALERT ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  LogPHASE ; 
 int MPSERVER_CONNECTED ; 
 int MPSERVER_FAILED ; 
 int MPSERVER_LISTENING ; 
 int /*<<< orphan*/  PF_LOCAL ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 char* _PATH_VARRUN ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mpserver_Close (struct mpserver*) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int snprintf (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int umask (int) ; 

int
mpserver_Open(struct mpserver *s, struct peerid *peer)
{
  int f, l;
  mode_t mask;

  if (s->fd != -1) {
    log_Printf(LogALERT, "Internal error !  mpserver already open\n");
    mpserver_Close(s);
  }

  l = snprintf(s->socket.sun_path, sizeof s->socket.sun_path, "%sppp-%s-%02x-",
               _PATH_VARRUN, peer->authname, peer->enddisc.class);
  if (l < 0) {
    log_Printf(LogERROR, "mpserver: snprintf(): %s\n", strerror(errno));
    return MPSERVER_FAILED;
  }

  for (f = 0;
       f < peer->enddisc.len && (size_t)l < sizeof s->socket.sun_path - 2;
       f++) {
    snprintf(s->socket.sun_path + l, sizeof s->socket.sun_path - l,
             "%02x", *(u_char *)(peer->enddisc.address+f));
    l += 2;
  }

  s->socket.sun_family = AF_LOCAL;
  s->socket.sun_len = sizeof s->socket;
  s->fd = ID0socket(PF_LOCAL, SOCK_DGRAM, 0);
  if (s->fd < 0) {
    log_Printf(LogERROR, "mpserver: socket(): %s\n", strerror(errno));
    return MPSERVER_FAILED;
  }

  setsockopt(s->fd, SOL_SOCKET, SO_REUSEADDR, (struct sockaddr *)&s->socket,
             sizeof s->socket);
  mask = umask(0177);

  /*
   * Try to bind the socket.  If we succeed we play server, if we fail
   * we connect() and hand the link off.
   */

  if (ID0bind_un(s->fd, &s->socket) < 0) {
    if (errno != EADDRINUSE) {
      log_Printf(LogPHASE, "mpserver: can't create bundle socket %s (%s)\n",
                s->socket.sun_path, strerror(errno));
      umask(mask);
      close(s->fd);
      s->fd = -1;
      return MPSERVER_FAILED;
    }

    /* So we're the sender */
    umask(mask);
    if (ID0connect_un(s->fd, &s->socket) < 0) {
      log_Printf(LogPHASE, "mpserver: can't connect to bundle socket %s (%s)\n",
                s->socket.sun_path, strerror(errno));
      if (errno == ECONNREFUSED)
        log_Printf(LogPHASE, "          The previous server died badly !\n");
      close(s->fd);
      s->fd = -1;
      return MPSERVER_FAILED;
    }

    /* Donate our link to the other guy */
    return MPSERVER_CONNECTED;
  }

  return MPSERVER_LISTENING;
}