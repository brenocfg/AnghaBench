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
struct wpa_supplicant {int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
struct TYPE_2__ {int (* set_bssid_blacklist ) (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline int wpa_drv_set_bssid_blacklist(struct wpa_supplicant *wpa_s,
					      unsigned int num_bssid,
					      const u8 *bssids)
{
	if (!wpa_s->driver->set_bssid_blacklist)
		return -1;
	return wpa_s->driver->set_bssid_blacklist(wpa_s->drv_priv, num_bssid,
						  bssids);
}