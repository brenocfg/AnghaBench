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
typedef  scalar_t__ u_short ;
typedef  void* u_int8_t ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {void* sin6_len; void* sin6_port; int /*<<< orphan*/  sin6_family; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; void* sin_len; void* sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct bundle {int dummy; } ;
typedef  int /*<<< orphan*/  off ;
typedef  enum server_stat { ____Placeholder_server_stat } server_stat ;
struct TYPE_8__ {scalar_t__ ipv6_available; } ;
struct TYPE_6__ {scalar_t__ port; char* sockname; scalar_t__ mask; } ;
struct TYPE_7__ {int fd; TYPE_2__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_V6ONLY ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  LogPHASE ; 
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int SERVER_FAILED ; 
 int SERVER_INVALID ; 
 int SERVER_OK ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 void* htons (scalar_t__) ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,char,int) ; 
 TYPE_4__ probe ; 
 TYPE_3__ server ; 
 int /*<<< orphan*/  server_Close (struct bundle*) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strerror (int /*<<< orphan*/ ) ; 

enum server_stat
server_TcpOpen(struct bundle *bundle, u_short port)
{
  struct sockaddr_storage ss;
  struct sockaddr_in *sin = (struct sockaddr_in *)&ss;
#ifndef NOINET6
  struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)&ss;
#endif
  int s, sz;

  if (server.cfg.port == port)
    server_Close(bundle);

  if (port == 0)
    return SERVER_INVALID;

  memset(&ss, '\0', sizeof ss);
#ifndef NOINET6
  if (probe.ipv6_available) {
    sin6->sin6_family = AF_INET6;
    sin6->sin6_port = htons(port);
    sin6->sin6_len = (u_int8_t)sizeof ss;
    sz = sizeof *sin6;
    s = socket(PF_INET6, SOCK_STREAM, 0);
  } else
#endif
  {
    sin->sin_family = AF_INET;
    sin->sin_port = htons(port);
    sin->sin_len = (u_int8_t)sizeof ss;
    sin->sin_addr.s_addr = INADDR_ANY;
    sz = sizeof *sin;
    s = socket(PF_INET, SOCK_STREAM, 0);
  }

  if (s < 0) {
    log_Printf(LogERROR, "Tcp: socket: %s\n", strerror(errno));
    goto failed;
  }

#ifndef NOINET6
  if (probe.ipv6_available) {
    int off = 0;
    setsockopt(s, IPPROTO_IPV6, IPV6_V6ONLY, (char *)&off, sizeof(off));
  }
#endif

  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &s, sizeof s);
  if (bind(s, (struct sockaddr *)&ss, sz) < 0) {
    log_Printf(LogWARN, "Tcp: bind: %s\n", strerror(errno));
    close(s);
    goto failed;
  }
  if (listen(s, 5) != 0) {
    log_Printf(LogERROR, "Tcp: Unable to listen to socket: %s\n",
               strerror(errno));
    close(s);
    goto failed;
  }
  server_Close(bundle);
  server.fd = s;
  server.cfg.port = port;
  *server.cfg.sockname = '\0';
  server.cfg.mask = 0;
  log_Printf(LogPHASE, "Listening at port %d.\n", port);
  return SERVER_OK;

failed:
  if (server.fd == -1) {
    server.fd = -1;
    server.cfg.port = port;
    *server.cfg.sockname = '\0';
    server.cfg.mask = 0;
  }
  return SERVER_FAILED;
}