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
struct sockaddr_un {int sun_len; int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
struct bundle {int dummy; } ;
typedef  scalar_t__ mode_t ;
typedef  enum server_stat { ____Placeholder_server_stat } server_stat ;
struct TYPE_3__ {char* sockname; scalar_t__ mask; scalar_t__ port; } ;
struct TYPE_4__ {int fd; TYPE_1__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LOCAL ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  LogPHASE ; 
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  PF_LOCAL ; 
 int SERVER_FAILED ; 
 int SERVER_INVALID ; 
 int SERVER_OK ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,char,int) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  server_Close (struct bundle*) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 char const* strerror (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ umask (scalar_t__) ; 
 int /*<<< orphan*/  unlink (char const*) ; 

enum server_stat
server_LocalOpen(struct bundle *bundle, const char *name, mode_t mask)
{
  struct sockaddr_un ifsun;
  mode_t oldmask;
  int s;

  oldmask = (mode_t)-1;		/* Silence compiler */

  if (server.cfg.sockname[0] != '\0' && !strcmp(server.cfg.sockname, name))
    server_Close(bundle);

  memset(&ifsun, '\0', sizeof ifsun);
  ifsun.sun_len = strlen(name);
  if (ifsun.sun_len > sizeof ifsun.sun_path - 1) {
    log_Printf(LogERROR, "Local: %s: Path too long\n", name);
    return SERVER_INVALID;
  }
  ifsun.sun_family = AF_LOCAL;
  strcpy(ifsun.sun_path, name);

  s = socket(PF_LOCAL, SOCK_STREAM, 0);
  if (s < 0) {
    log_Printf(LogERROR, "Local: socket: %s\n", strerror(errno));
    goto failed;
  }
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &s, sizeof s);
  if (mask != (mode_t)-1)
    oldmask = umask(mask);
  if (bind(s, (struct sockaddr *)&ifsun, sizeof ifsun) < 0) {
    if (mask != (mode_t)-1)
      umask(oldmask);
    log_Printf(LogWARN, "Local: bind: %s\n", strerror(errno));
    close(s);
    goto failed;
  }
  if (mask != (mode_t)-1)
    umask(oldmask);
  if (listen(s, 5) != 0) {
    log_Printf(LogERROR, "Local: Unable to listen to socket -"
               " BUNDLE overload?\n");
    close(s);
    unlink(name);
    goto failed;
  }
  server_Close(bundle);
  server.fd = s;
  server.cfg.port = 0;
  strncpy(server.cfg.sockname, ifsun.sun_path, sizeof server.cfg.sockname - 1);
  server.cfg.sockname[sizeof server.cfg.sockname - 1] = '\0';
  server.cfg.mask = mask;
  log_Printf(LogPHASE, "Listening at local socket %s.\n", name);

  return SERVER_OK;

failed:
  if (server.fd == -1) {
    server.fd = -1;
    server.cfg.port = 0;
    strncpy(server.cfg.sockname, ifsun.sun_path,
            sizeof server.cfg.sockname - 1);
    server.cfg.sockname[sizeof server.cfg.sockname - 1] = '\0';
    server.cfg.mask = mask;
  }
  return SERVER_FAILED;
}