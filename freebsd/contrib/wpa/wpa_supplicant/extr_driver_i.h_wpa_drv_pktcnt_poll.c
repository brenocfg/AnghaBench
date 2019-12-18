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
struct wpa_supplicant {int /*<<< orphan*/  bssid; int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
struct hostap_sta_driver_data {int dummy; } ;
struct TYPE_2__ {int (* read_sta_data ) (int /*<<< orphan*/ ,struct hostap_sta_driver_data*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,struct hostap_sta_driver_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int wpa_drv_pktcnt_poll(struct wpa_supplicant *wpa_s,
				      struct hostap_sta_driver_data *sta)
{
	if (wpa_s->driver->read_sta_data)
		return wpa_s->driver->read_sta_data(wpa_s->drv_priv, sta,
						    wpa_s->bssid);
	return -1;
}