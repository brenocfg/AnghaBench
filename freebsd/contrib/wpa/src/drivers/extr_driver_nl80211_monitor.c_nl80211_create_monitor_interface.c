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
struct wpa_driver_nl80211_data {int device_ap_sme; scalar_t__ monitor_sock; int /*<<< orphan*/  monitor_refcount; int /*<<< orphan*/  monitor_ifidx; TYPE_2__* global; TYPE_1__* first_bss; } ;
struct sockaddr_ll {int /*<<< orphan*/  sll_ifindex; int /*<<< orphan*/  sll_family; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  optval ;
typedef  int /*<<< orphan*/  ll ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {int /*<<< orphan*/  ioctl_sock; } ;
struct TYPE_3__ {char* ifname; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_PACKET ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_P_ALL ; 
 int IFNAMSIZ ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MONITOR ; 
 int /*<<< orphan*/  PF_PACKET ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_PRIORITY ; 
 scalar_t__ add_monitor_filter (scalar_t__) ; 
 scalar_t__ bind (scalar_t__,struct sockaddr*,int) ; 
 scalar_t__ eloop_register_read_sock (scalar_t__,int /*<<< orphan*/ ,struct wpa_driver_nl80211_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  handle_monitor_read ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ linux_set_iface_flags (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_ll*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nl80211_create_iface (struct wpa_driver_nl80211_data*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl80211_remove_monitor_interface (struct wpa_driver_nl80211_data*) ; 
 int os_snprintf (char*,int,char*,char*) ; 
 scalar_t__ os_strncmp (char*,char*,int) ; 
 scalar_t__ setsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int nl80211_create_monitor_interface(struct wpa_driver_nl80211_data *drv)
{
	char buf[IFNAMSIZ];
	struct sockaddr_ll ll;
	int optval;
	socklen_t optlen;

	if (drv->monitor_ifidx >= 0) {
		drv->monitor_refcount++;
		wpa_printf(MSG_DEBUG, "nl80211: Re-use existing monitor interface: refcount=%d",
			   drv->monitor_refcount);
		return 0;
	}

	if (os_strncmp(drv->first_bss->ifname, "p2p-", 4) == 0) {
		/*
		 * P2P interface name is of the format p2p-%s-%d. For monitor
		 * interface name corresponding to P2P GO, replace "p2p-" with
		 * "mon-" to retain the same interface name length and to
		 * indicate that it is a monitor interface.
		 */
		snprintf(buf, IFNAMSIZ, "mon-%s", drv->first_bss->ifname + 4);
	} else {
		int ret;

		/* Non-P2P interface with AP functionality. */
		ret = os_snprintf(buf, IFNAMSIZ, "mon.%s",
				  drv->first_bss->ifname);
		if (ret >= (int) sizeof(buf))
			wpa_printf(MSG_DEBUG,
				   "nl80211: Monitor interface name has been truncated to %s",
				   buf);
		else if (ret < 0)
			return ret;
	}

	buf[IFNAMSIZ - 1] = '\0';

	drv->monitor_ifidx =
		nl80211_create_iface(drv, buf, NL80211_IFTYPE_MONITOR, NULL,
				     0, NULL, NULL, 0);

	if (drv->monitor_ifidx == -EOPNOTSUPP) {
		/*
		 * This is backward compatibility for a few versions of
		 * the kernel only that didn't advertise the right
		 * attributes for the only driver that then supported
		 * AP mode w/o monitor -- ath6kl.
		 */
		wpa_printf(MSG_DEBUG, "nl80211: Driver does not support "
			   "monitor interface type - try to run without it");
		drv->device_ap_sme = 1;
	}

	if (drv->monitor_ifidx < 0)
		return -1;

	if (linux_set_iface_flags(drv->global->ioctl_sock, buf, 1))
		goto error;

	memset(&ll, 0, sizeof(ll));
	ll.sll_family = AF_PACKET;
	ll.sll_ifindex = drv->monitor_ifidx;
	drv->monitor_sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (drv->monitor_sock < 0) {
		wpa_printf(MSG_ERROR, "nl80211: socket[PF_PACKET,SOCK_RAW] failed: %s",
			   strerror(errno));
		goto error;
	}

	if (add_monitor_filter(drv->monitor_sock)) {
		wpa_printf(MSG_INFO, "Failed to set socket filter for monitor "
			   "interface; do filtering in user space");
		/* This works, but will cost in performance. */
	}

	if (bind(drv->monitor_sock, (struct sockaddr *) &ll, sizeof(ll)) < 0) {
		wpa_printf(MSG_ERROR, "nl80211: monitor socket bind failed: %s",
			   strerror(errno));
		goto error;
	}

	optlen = sizeof(optval);
	optval = 20;
	if (setsockopt
	    (drv->monitor_sock, SOL_SOCKET, SO_PRIORITY, &optval, optlen)) {
		wpa_printf(MSG_ERROR, "nl80211: Failed to set socket priority: %s",
			   strerror(errno));
		goto error;
	}

	if (eloop_register_read_sock(drv->monitor_sock, handle_monitor_read,
				     drv, NULL)) {
		wpa_printf(MSG_INFO, "nl80211: Could not register monitor read socket");
		goto error;
	}

	drv->monitor_refcount++;
	return 0;
 error:
	nl80211_remove_monitor_interface(drv);
	return -1;
}