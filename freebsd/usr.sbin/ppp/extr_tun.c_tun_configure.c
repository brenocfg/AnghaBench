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
struct tuninfo {int flags; int /*<<< orphan*/  baudrate; int /*<<< orphan*/  mtu; int /*<<< orphan*/  type; } ;
struct ifreq {int /*<<< orphan*/  ifr_mtu; int /*<<< orphan*/  ifr_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  fd; } ;
struct bundle {int unit; TYPE_2__ dev; int /*<<< orphan*/  bandwidth; TYPE_1__* iface; } ;
struct TYPE_3__ {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 scalar_t__ ID0ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tuninfo*) ; 
 int IFF_MULTICAST ; 
 int IFF_POINTOPOINT ; 
 int IFF_UP ; 
 int /*<<< orphan*/  IFT_PPP ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SIOCSIFMTU ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  TUNSIFINFO ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct tuninfo*,char,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void
tun_configure(struct bundle *bundle)
{
#ifdef __NetBSD__
  struct ifreq ifr;
  int s;

  s = socket(PF_INET, SOCK_DGRAM, 0);

  if (s < 0) {
    log_Printf(LogERROR, "tun_configure: socket(): %s\n", strerror(errno));
    return;
  }

  sprintf(ifr.ifr_name, "tun%d", bundle->unit);
  ifr.ifr_mtu = bundle->iface->mtu;
  if (ioctl(s, SIOCSIFMTU, &ifr) < 0)
      log_Printf(LogERROR, "tun_configure: ioctl(SIOCSIFMTU): %s\n",
             strerror(errno));

  close(s);
#else
  struct tuninfo info;

  memset(&info, '\0', sizeof info);
  info.type = IFT_PPP;
  info.mtu = bundle->iface->mtu;

  info.baudrate = bundle->bandwidth;
#ifdef __OpenBSD__
  info.flags = IFF_UP|IFF_POINTOPOINT|IFF_MULTICAST;
#endif
  if (ID0ioctl(bundle->dev.fd, TUNSIFINFO, &info) < 0)
    log_Printf(LogERROR, "tun_configure: ioctl(TUNSIFINFO): %s\n",
	      strerror(errno));
#endif
}