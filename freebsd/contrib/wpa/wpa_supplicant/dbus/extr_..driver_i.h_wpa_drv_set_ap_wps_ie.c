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
struct wpabuf {int dummy; } ;
struct wpa_supplicant {int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
struct TYPE_2__ {int (* set_ap_wps_ie ) (int /*<<< orphan*/ ,struct wpabuf const*,struct wpabuf const*,struct wpabuf const*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,struct wpabuf const*,struct wpabuf const*,struct wpabuf const*) ; 

__attribute__((used)) static inline int wpa_drv_set_ap_wps_ie(struct wpa_supplicant *wpa_s,
					const struct wpabuf *beacon,
					const struct wpabuf *proberesp,
					const struct wpabuf *assocresp)
{
	if (!wpa_s->driver->set_ap_wps_ie)
		return -1;
	return wpa_s->driver->set_ap_wps_ie(wpa_s->drv_priv, beacon,
					    proberesp, assocresp);
}