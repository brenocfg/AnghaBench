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
struct TYPE_4__ {char* buffer; scalar_t__ length; } ;
struct ifreq {TYPE_2__ ifr_buffer; int /*<<< orphan*/  ifr_name; } ;
struct iface {char* descr; int /*<<< orphan*/  name; } ;
struct cmdargs {int argn; int argc; char** argv; TYPE_1__* bundle; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_3__ {struct iface* iface; } ;

/* Variables and functions */
 scalar_t__ ID0ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ID0socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SIOCSIFDESCR ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,...) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 size_t strlcat (char*,char*,size_t) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
iface_Descr(struct cmdargs const *arg)
{
  struct ifreq ifr;
  struct iface *iface;
  size_t sz, len;
  int s, n, ifdescr_maxlen;
  char *descr;

  sz = sizeof(int);
  if (sysctlbyname("net.ifdescr_maxlen", &ifdescr_maxlen, &sz, NULL, 0) < 0) {
    log_Printf(LogERROR, "iface descr: sysctl failed: %s\n", strerror(errno));
    return 1;
  }

  if (ifdescr_maxlen < 1) {
    log_Printf(LogERROR, "iface descr: sysctl net.ifdescr_maxlen < 1\n");
    return 1;
  }

  sz = sizeof(char) * ifdescr_maxlen;
  if ((descr = malloc(sz)) == NULL) {
    log_Printf(LogERROR, "iface descr: malloc failed: %s\n", strerror(errno));
    return 1;
  }

  *descr = '\0';
  n = arg->argn;
  while (n < arg->argc) {
    if (n > arg->argn && (len = strlcat(descr, " ", sz)) >= sz)
      break;
    if ((len = strlcat(descr, arg->argv[n], sz)) >= sz)
      break;
    ++n;
  }
  if (len >= sz) {
    log_Printf(LogERROR, "iface descr: description exceeds maximum (%d)\n",
               ifdescr_maxlen-1);
    free(descr);
    return 1;
  }

  if ((s = ID0socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
    log_Printf(LogERROR, "iface descr: socket(): %s\n", strerror(errno));
    free(descr);
    return 1;
  }

  iface = arg->bundle->iface;
  strlcpy(ifr.ifr_name, iface->name, sizeof(ifr.ifr_name));
  ifr.ifr_buffer.length = strlen(descr) + 1;
  ifr.ifr_buffer.buffer = descr;
  if (ID0ioctl(s, SIOCSIFDESCR, (caddr_t)&ifr) < 0) {
    log_Printf(LogWARN, "iface descr: ioctl(SIOCSIFDESCR, %s): %s\n",
               descr, strerror(errno));
    free(descr);
    return 1;
  }

  free(iface->descr);
  iface->descr = descr;

  return 0;
}