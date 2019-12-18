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
typedef  int /*<<< orphan*/  u8 ;
struct openbsd_driver_data {int /*<<< orphan*/  sock; int /*<<< orphan*/  ifname; } ;
struct ieee80211_bssid {int /*<<< orphan*/  i_bssid; int /*<<< orphan*/  i_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ADDR_LEN ; 
 int /*<<< orphan*/  SIOCG80211BSSID ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_bssid*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
wpa_driver_openbsd_get_bssid(void *priv, u8 *bssid)
{
	struct openbsd_driver_data *drv = priv;
	struct ieee80211_bssid id;

	os_strlcpy(id.i_name, drv->ifname, sizeof(id.i_name));
	if (ioctl(drv->sock, SIOCG80211BSSID, &id) < 0)
		return -1;

	os_memcpy(bssid, id.i_bssid, IEEE80211_ADDR_LEN);
	return 0;
}