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
struct wlan_iface {int /*<<< orphan*/  wname; int /*<<< orphan*/  stats; } ;
struct ifreq {scalar_t__ ifr_data; int /*<<< orphan*/  ifr_name; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SIOCG80211STATS ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sock ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
wlan_get_stats(struct wlan_iface *wif)
{
	struct ifreq ifr;

	memset(&ifr, 0, sizeof(struct ifreq));
	strlcpy(ifr.ifr_name, wif->wname, IFNAMSIZ);

	ifr.ifr_data = (caddr_t) &wif->stats;

	if (ioctl(sock, SIOCG80211STATS, &ifr) < 0) {
		syslog(LOG_ERR, "iface %s - ioctl(SIOCG80211STATS) failed: %s",
		    wif->wname, strerror(errno));
		return (-1);
	}

	return (0);
}