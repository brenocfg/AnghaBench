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
struct bsd_driver_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IOC_OPTIE ; 
 int bsd_set_opt_ie (struct bsd_driver_data*,int /*<<< orphan*/  const*,size_t) ; 
 int set80211var (struct bsd_driver_data*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int
wpa_driver_bsd_set_wpa_ie(struct bsd_driver_data *drv, const u8 *wpa_ie,
			  size_t wpa_ie_len)
{
#ifdef IEEE80211_IOC_APPIE
	return bsd_set_opt_ie(drv, wpa_ie, wpa_ie_len);
#else /* IEEE80211_IOC_APPIE */
	return set80211var(drv, IEEE80211_IOC_OPTIE, wpa_ie, wpa_ie_len);
#endif /* IEEE80211_IOC_APPIE */
}