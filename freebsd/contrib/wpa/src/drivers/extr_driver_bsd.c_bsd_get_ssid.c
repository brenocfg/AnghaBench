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
typedef  int /*<<< orphan*/  u8 ;
struct ifreq {void* ifr_data; int /*<<< orphan*/  ifr_name; } ;
struct ieee80211_nwid {scalar_t__ i_len; int /*<<< orphan*/  i_nwid; } ;
struct bsd_driver_data {TYPE_1__* global; int /*<<< orphan*/  ifname; } ;
typedef  int /*<<< orphan*/  ifr ;
struct TYPE_2__ {int /*<<< orphan*/  sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IOC_SSID ; 
 scalar_t__ IEEE80211_NWID_LEN ; 
 int /*<<< orphan*/  SIOCG80211NWID ; 
 int get80211var (struct bsd_driver_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  os_memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bsd_get_ssid(void *priv, u8 *ssid, int len)
{
	struct bsd_driver_data *drv = priv;
#ifdef SIOCG80211NWID
	struct ieee80211_nwid nwid;
	struct ifreq ifr;

	os_memset(&ifr, 0, sizeof(ifr));
	os_strlcpy(ifr.ifr_name, drv->ifname, sizeof(ifr.ifr_name));
	ifr.ifr_data = (void *)&nwid;
	if (ioctl(drv->global->sock, SIOCG80211NWID, &ifr) < 0 ||
	    nwid.i_len > IEEE80211_NWID_LEN)
		return -1;
	os_memcpy(ssid, nwid.i_nwid, nwid.i_len);
	return nwid.i_len;
#else
	return get80211var(drv, IEEE80211_IOC_SSID, ssid, IEEE80211_NWID_LEN);
#endif
}