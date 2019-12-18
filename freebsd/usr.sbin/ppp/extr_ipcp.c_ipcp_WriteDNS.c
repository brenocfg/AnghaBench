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
struct TYPE_3__ {TYPE_2__* dns; scalar_t__ resolv_nons; } ;
struct ipcp {TYPE_1__ ns; } ;
typedef  int mode_t ;
struct TYPE_4__ {scalar_t__ s_addr; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/ * ID0fopen (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ INADDR_ANY ; 
 scalar_t__ INADDR_NONE ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  LogIPCP ; 
 int /*<<< orphan*/  _PATH_RESCONF ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  fputs (scalar_t__,int /*<<< orphan*/ *) ; 
 char* inet_ntoa (TYPE_2__) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int umask (int) ; 

int
ipcp_WriteDNS(struct ipcp *ipcp)
{
  const char *paddr;
  mode_t mask;
  FILE *fp;

  if (ipcp->ns.dns[0].s_addr == INADDR_ANY &&
      ipcp->ns.dns[1].s_addr == INADDR_ANY) {
    log_Printf(LogIPCP, "%s not modified: All nameservers NAKd\n",
              _PATH_RESCONF);
    return 0;
  }

  if (ipcp->ns.dns[0].s_addr == INADDR_ANY) {
    ipcp->ns.dns[0].s_addr = ipcp->ns.dns[1].s_addr;
    ipcp->ns.dns[1].s_addr = INADDR_ANY;
  }

  mask = umask(022);
  if ((fp = ID0fopen(_PATH_RESCONF, "w")) != NULL) {
    umask(mask);
    if (ipcp->ns.resolv_nons)
      fputs(ipcp->ns.resolv_nons, fp);
    paddr = inet_ntoa(ipcp->ns.dns[0]);
    log_Printf(LogIPCP, "Primary nameserver set to %s\n", paddr);
    fprintf(fp, "\nnameserver %s\n", paddr);
    if (ipcp->ns.dns[1].s_addr != INADDR_ANY &&
        ipcp->ns.dns[1].s_addr != INADDR_NONE &&
        ipcp->ns.dns[1].s_addr != ipcp->ns.dns[0].s_addr) {
      paddr = inet_ntoa(ipcp->ns.dns[1]);
      log_Printf(LogIPCP, "Secondary nameserver set to %s\n", paddr);
      fprintf(fp, "nameserver %s\n", paddr);
    }
    if (fclose(fp) == EOF) {
      log_Printf(LogERROR, "write(): Failed updating %s: %s\n", _PATH_RESCONF,
                 strerror(errno));
      return 0;
    }
  } else {
    umask(mask);
    log_Printf(LogERROR,"fopen(\"%s\", \"w\") failed: %s\n", _PATH_RESCONF,
                 strerror(errno));
  }

  return 1;
}