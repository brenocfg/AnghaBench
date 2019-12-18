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
typedef  scalar_t__ uint8_t ;
struct wlan_iface {scalar_t__ state; int /*<<< orphan*/  wname; } ;
struct ifreq {int ifr_flags; int ifr_flagshigh; int /*<<< orphan*/  ifr_name; } ;
typedef  int /*<<< orphan*/  ifr ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SIOCGIFFLAGS ; 
 int /*<<< orphan*/  SIOCSIFFLAGS ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sock ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ wlanIfaceState_down ; 
 scalar_t__ wlanIfaceState_up ; 

int
wlan_config_state(struct wlan_iface *wif, uint8_t set)
{
	int	flags;
	struct ifreq ifr;

	memset(&ifr, 0, sizeof(ifr));
	strcpy(ifr.ifr_name, wif->wname);

	if (ioctl(sock, SIOCGIFFLAGS, (caddr_t) &ifr) < 0) {
		syslog(LOG_ERR, "set %s status: ioctl(SIOCGIFFLAGS) "
		    "failed: %s", wif->wname, strerror(errno));
		return (-1);
	}

	if (set == 0) {
		if ((ifr.ifr_flags & IFF_UP) != 0)
			wif->state = wlanIfaceState_up;
		else
			wif->state = wlanIfaceState_down;
		return (0);
	}

	flags = (ifr.ifr_flags & 0xffff) | (ifr.ifr_flagshigh << 16);

	if (wif->state == wlanIfaceState_up)
		flags |= IFF_UP;
	else
		flags &= ~IFF_UP;

	ifr.ifr_flags = flags & 0xffff;
	ifr.ifr_flagshigh = flags >> 16;
	if (ioctl(sock, SIOCSIFFLAGS, (caddr_t) &ifr) < 0) {
		syslog(LOG_ERR, "set %s %s: ioctl(SIOCSIFFLAGS) failed: %s",
		    wif->wname, wif->state == wlanIfaceState_up?"up":"down",
		    strerror(errno));
		return (-1);
	}

	return (0);
}