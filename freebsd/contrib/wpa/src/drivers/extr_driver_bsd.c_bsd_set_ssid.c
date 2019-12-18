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
struct ieee80211_nwid {int i_len; int /*<<< orphan*/  i_nwid; } ;
struct bsd_driver_data {TYPE_1__* global; int /*<<< orphan*/  ifname; } ;
typedef  int /*<<< orphan*/  ifr ;
struct TYPE_2__ {int /*<<< orphan*/  sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IOC_SSID ; 
 int /*<<< orphan*/  SIOCS80211NWID ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  os_memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int set80211var (struct bsd_driver_data*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int
bsd_set_ssid(void *priv, const u8 *ssid, int ssid_len)
{
	struct bsd_driver_data *drv = priv;
#ifdef SIOCS80211NWID
	struct ieee80211_nwid nwid;
	struct ifreq ifr;

	os_memcpy(nwid.i_nwid, ssid, ssid_len);
	nwid.i_len = ssid_len;
	os_memset(&ifr, 0, sizeof(ifr));
	os_strlcpy(ifr.ifr_name, drv->ifname, sizeof(ifr.ifr_name));
	ifr.ifr_data = (void *)&nwid;
	return ioctl(drv->global->sock, SIOCS80211NWID, &ifr);
#else
	return set80211var(drv, IEEE80211_IOC_SSID, ssid, ssid_len);
#endif
}