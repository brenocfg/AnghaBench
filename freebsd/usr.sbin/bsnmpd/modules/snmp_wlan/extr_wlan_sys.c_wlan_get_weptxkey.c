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
struct wlan_iface {int weptxkey; int /*<<< orphan*/  wname; int /*<<< orphan*/  wepsupported; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IOC_WEPTXKEY ; 
 int IEEE80211_KEYIX_NONE ; 
 scalar_t__ wlan_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ; 

int
wlan_get_weptxkey(struct wlan_iface *wif)
{
	int val;
	size_t argsize = 0;

	if (!wif->wepsupported)
		return (0);

	if (wlan_ioctl(wif->wname, IEEE80211_IOC_WEPTXKEY, &val, NULL,
	    &argsize, 0) < 0)
		return (-1);

	if (val == IEEE80211_KEYIX_NONE)
		wif->weptxkey = 0;
	else
		wif->weptxkey = val + 1;

	return (0);
}