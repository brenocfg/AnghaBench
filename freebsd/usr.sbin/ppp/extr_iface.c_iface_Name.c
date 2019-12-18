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
struct ifreq {char* ifr_data; int /*<<< orphan*/  ifr_name; } ;
struct iface {char* name; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ ID0ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ID0socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SIOCSIFNAME ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

int
iface_Name(struct iface *iface, const char *name)
{
  struct ifreq ifr;
  int s;
  char *newname;

  if ((newname = strdup(name)) == NULL) {
    log_Printf(LogWARN, "iface name: strdup failed: %s\n", strerror(errno));
    return 0;
  }

  if ((s = ID0socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
    log_Printf(LogERROR, "iface name: socket(): %s\n", strerror(errno));
    free(newname);
    return 0;
  }

  strlcpy(ifr.ifr_name, iface->name, sizeof(ifr.ifr_name));
  ifr.ifr_data = newname;
  if (ID0ioctl(s, SIOCSIFNAME, (caddr_t)&ifr) < 0) {
    log_Printf(LogWARN, "iface name: ioctl(SIOCSIFNAME, %s -> %s): %s\n",
               name, newname, strerror(errno));
    free(newname);
    return 0;
  }

  free(iface->name);
  iface->name = newname;

  return 1;
}