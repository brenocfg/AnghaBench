#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ifreq {int /*<<< orphan*/  ifr_name; } ;
struct iface {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ ID0ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ID0socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SIOCIFDESTROY ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  iface_Free (struct iface*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
iface_Destroy(struct iface *iface)
{
  struct ifreq ifr;
  int s;

  if (iface != NULL) {
    if ((s = ID0socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
      log_Printf(LogERROR, "iface_Destroy: socket(): %s\n", strerror(errno));
    } else {
      strlcpy(ifr.ifr_name, iface->name, sizeof(ifr.ifr_name));
      if (ID0ioctl(s, SIOCIFDESTROY, (caddr_t)&ifr) < 0)
        log_Printf(LogWARN, "iface_Destroy: ioctl(SIOCIFDESTROY, %s): %s\n",
               iface->name, strerror(errno));
    }
    iface_Free(iface);
  }
}