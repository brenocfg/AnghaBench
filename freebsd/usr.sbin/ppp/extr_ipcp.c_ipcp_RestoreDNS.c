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
struct TYPE_2__ {int /*<<< orphan*/  resolv; scalar_t__ resolver; } ;
struct ipcp {TYPE_1__ ns; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ID0open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  LogERROR ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  _PATH_RESCONF ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,long,...) ; 
 int remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int write (int,int /*<<< orphan*/ ,int) ; 

void
ipcp_RestoreDNS(struct ipcp *ipcp)
{
  if (ipcp->ns.resolver) {
    ssize_t got, len;
    int fd;

    if ((fd = ID0open(_PATH_RESCONF, O_WRONLY|O_TRUNC, 0644)) != -1) {
      len = strlen(ipcp->ns.resolv);
      if ((got = write(fd, ipcp->ns.resolv, len)) != len) {
        if (got == -1)
          log_Printf(LogERROR, "Failed rewriting %s: write: %s\n",
                     _PATH_RESCONF, strerror(errno));
        else
          log_Printf(LogERROR, "Failed rewriting %s: wrote %ld of %ld\n",
                     _PATH_RESCONF, (long)got, (long)len);
      }
      close(fd);
    } else
      log_Printf(LogERROR, "Failed rewriting %s: open: %s\n", _PATH_RESCONF,
                 strerror(errno));
  } else if (remove(_PATH_RESCONF) == -1)
    log_Printf(LogERROR, "Failed removing %s: %s\n", _PATH_RESCONF,
               strerror(errno));

}