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
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct sockaddr {scalar_t__ sa_len; int sa_family; } ;
struct TYPE_3__ {int /*<<< orphan*/  sockname; } ;
struct server {scalar_t__ fd; TYPE_1__ cfg; } ;
struct TYPE_4__ {char* type; char* from; } ;
struct prompt {int /*<<< orphan*/  desc; struct prompt* next; TYPE_2__ src; } ;
struct ncpaddr {int dummy; } ;
struct fdescriptor {int dummy; } ;
struct bundle {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_LOCAL 128 
 scalar_t__ FD_ISSET (scalar_t__,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LogALERT ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  LogPHASE ; 
 int accept (scalar_t__,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  close (int) ; 
 struct server* descriptor2server (struct fdescriptor*) ; 
 scalar_t__ descriptor_IsSet (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  descriptor_Read (int /*<<< orphan*/ *,struct bundle*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,...) ; 
 struct prompt* log_PromptList () ; 
 scalar_t__ log_PromptListChanged ; 
 char* ncpaddr_ntoa (struct ncpaddr*) ; 
 int /*<<< orphan*/  ncpaddr_setsa (struct ncpaddr*,struct sockaddr*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 struct prompt* prompt_Create (struct server*,struct bundle*,int) ; 
 int /*<<< orphan*/  prompt_Required (struct prompt*) ; 
 int /*<<< orphan*/  prompt_TtyCommandMode (struct prompt*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

__attribute__((used)) static void
server_Read(struct fdescriptor *d, struct bundle *bundle, const fd_set *fdset)
{
  struct server *s = descriptor2server(d);
  struct sockaddr_storage ss;
  struct sockaddr *sa = (struct sockaddr *)&ss;
  struct sockaddr_in *sin = (struct sockaddr_in *)&ss;
#ifndef NOINET6
  struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)&ss;
#endif
  int ssize = sizeof ss, wfd;
  struct prompt *p;
  struct ncpaddr addr;

  if (s->fd >= 0 && FD_ISSET(s->fd, fdset)) {
    wfd = accept(s->fd, sa, &ssize);
    if (wfd < 0)
      log_Printf(LogERROR, "server_Read: accept(): %s\n", strerror(errno));
    else if (sa->sa_len == 0) {
      close(wfd);
      wfd = -1;
    }
  } else
    wfd = -1;

  if (wfd >= 0)
    switch (sa->sa_family) {
      case AF_LOCAL:
        log_Printf(LogPHASE, "Connected to local client.\n");
        break;

      case AF_INET:
        ncpaddr_setsa(&addr, sa);
        if (ntohs(sin->sin_port) < 1024) {
          log_Printf(LogALERT, "Rejected client connection from %s:%u"
                    "(invalid port number) !\n",
                    ncpaddr_ntoa(&addr), ntohs(sin->sin_port));
          close(wfd);
          wfd = -1;
          break;
        }
        log_Printf(LogPHASE, "Connected to client from %s:%u\n",
                  ncpaddr_ntoa(&addr), ntohs(sin->sin_port));
        break;

#ifndef NOINET6
      case AF_INET6:
        ncpaddr_setsa(&addr, sa);
        if (ntohs(sin6->sin6_port) < 1024) {
          log_Printf(LogALERT, "Rejected client connection from %s:%u"
                    "(invalid port number) !\n",
                    ncpaddr_ntoa(&addr), ntohs(sin6->sin6_port));
          close(wfd);
          wfd = -1;
          break;
        }
        log_Printf(LogPHASE, "Connected to client from %s:%u\n",
                  ncpaddr_ntoa(&addr), ntohs(sin6->sin6_port));
        break;
#endif

      default:
        write(wfd, "Unrecognised access !\n", 22);
        close(wfd);
        wfd = -1;
        break;
    }

  if (wfd >= 0) {
    if ((p = prompt_Create(s, bundle, wfd)) == NULL) {
      write(wfd, "Connection refused.\n", 20);
      close(wfd);
    } else {
      switch (sa->sa_family) {
        case AF_LOCAL:
          p->src.type = "local";
          strncpy(p->src.from, s->cfg.sockname, sizeof p->src.from - 1);
          p->src.from[sizeof p->src.from - 1] = '\0';
          break;
        case AF_INET:
          p->src.type = "ip";
          snprintf(p->src.from, sizeof p->src.from, "%s:%u",
                   ncpaddr_ntoa(&addr), ntohs(sin->sin_port));
          break;
#ifndef NOINET6
        case AF_INET6:
          p->src.type = "ip6";
          snprintf(p->src.from, sizeof p->src.from, "%s:%u",
                   ncpaddr_ntoa(&addr), ntohs(sin6->sin6_port));
          break;
#endif
      }
      prompt_TtyCommandMode(p);
      prompt_Required(p);
    }
  }

  log_PromptListChanged = 0;
  for (p = log_PromptList(); p; p = p->next)
    if (descriptor_IsSet(&p->desc, fdset)) {
      descriptor_Read(&p->desc, bundle, fdset);
      if (log_PromptListChanged)
        break;
    }
}