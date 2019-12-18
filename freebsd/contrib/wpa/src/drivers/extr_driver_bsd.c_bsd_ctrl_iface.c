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
struct ifreq {int ifr_flags; int /*<<< orphan*/  ifr_name; } ;
struct bsd_driver_data {int flags; TYPE_1__* global; int /*<<< orphan*/  ifname; } ;
typedef  int /*<<< orphan*/  ifr ;
struct TYPE_2__ {int /*<<< orphan*/  sock; } ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  SIOCGIFFLAGS ; 
 int /*<<< orphan*/  SIOCSIFFLAGS ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  os_memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bsd_ctrl_iface(void *priv, int enable)
{
	struct bsd_driver_data *drv = priv;
	struct ifreq ifr;

	os_memset(&ifr, 0, sizeof(ifr));
	os_strlcpy(ifr.ifr_name, drv->ifname, sizeof(ifr.ifr_name));

	if (ioctl(drv->global->sock, SIOCGIFFLAGS, &ifr) < 0) {
		wpa_printf(MSG_ERROR, "ioctl[SIOCGIFFLAGS]: %s",
			   strerror(errno));
		return -1;
	}
	drv->flags = ifr.ifr_flags;

	if (enable) {
		if (ifr.ifr_flags & IFF_UP)
			return 0;
		ifr.ifr_flags |= IFF_UP;
	} else {
		if (!(ifr.ifr_flags & IFF_UP))
			return 0;
		ifr.ifr_flags &= ~IFF_UP;
	}

	if (ioctl(drv->global->sock, SIOCSIFFLAGS, &ifr) < 0) {
		wpa_printf(MSG_ERROR, "ioctl[SIOCSIFFLAGS]: %s",
			   strerror(errno));
		return -1;
	}

	drv->flags = ifr.ifr_flags;
	return 0;
}