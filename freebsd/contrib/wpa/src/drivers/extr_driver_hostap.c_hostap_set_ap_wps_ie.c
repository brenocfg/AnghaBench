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
struct wpabuf {int dummy; } ;
struct hostap_driver_data {scalar_t__ wps_ie_len; int /*<<< orphan*/ * wps_ie; } ;

/* Variables and functions */
 int hostapd_ioctl_set_generic_elem (struct hostap_driver_data*) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_memdup (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf const*) ; 
 scalar_t__ wpabuf_len (struct wpabuf const*) ; 

__attribute__((used)) static int hostap_set_ap_wps_ie(void *priv, const struct wpabuf *beacon,
				const struct wpabuf *proberesp,
				const struct wpabuf *assocresp)
{
	struct hostap_driver_data *drv = priv;

	/*
	 * Host AP driver supports only one set of extra IEs, so we need to
	 * use the Probe Response IEs also for Beacon frames since they include
	 * more information.
	 */

	os_free(drv->wps_ie);
	drv->wps_ie = NULL;
	drv->wps_ie_len = 0;
	if (proberesp) {
		drv->wps_ie = os_memdup(wpabuf_head(proberesp),
					wpabuf_len(proberesp));
		if (drv->wps_ie == NULL)
			return -1;
		drv->wps_ie_len = wpabuf_len(proberesp);
	}

	return hostapd_ioctl_set_generic_elem(drv);
}