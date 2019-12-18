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
struct wpa_driver_ndis_data {struct wpa_driver_ndis_data* adapter_desc; struct wpa_driver_ndis_data* adapter_name; scalar_t__ wzc_disabled; int /*<<< orphan*/ * ctx; scalar_t__ events; int /*<<< orphan*/  event_avail; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_driver_ndis_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_unregister_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ndis_events_deinit (scalar_t__) ; 
 int /*<<< orphan*/  ndisuio_notification_deinit (struct wpa_driver_ndis_data*) ; 
 int /*<<< orphan*/  os_free (struct wpa_driver_ndis_data*) ; 
 int /*<<< orphan*/  wpa_driver_ndis_adapter_close (struct wpa_driver_ndis_data*) ; 
 int /*<<< orphan*/  wpa_driver_ndis_disconnect (struct wpa_driver_ndis_data*) ; 
 int /*<<< orphan*/  wpa_driver_ndis_flush_pmkid (struct wpa_driver_ndis_data*) ; 
 int /*<<< orphan*/  wpa_driver_ndis_poll_timeout ; 
 scalar_t__ wpa_driver_ndis_radio_off (struct wpa_driver_ndis_data*) ; 
 int /*<<< orphan*/  wpa_driver_ndis_scan_timeout ; 
 int /*<<< orphan*/  wpa_driver_ndis_set_wzc (struct wpa_driver_ndis_data*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void wpa_driver_ndis_deinit(void *priv)
{
	struct wpa_driver_ndis_data *drv = priv;

#ifdef CONFIG_NDIS_EVENTS_INTEGRATED
	if (drv->events) {
		eloop_unregister_event(drv->event_avail,
				       sizeof(drv->event_avail));
		ndis_events_deinit(drv->events);
	}
#endif /* CONFIG_NDIS_EVENTS_INTEGRATED */

#ifdef _WIN32_WCE
	ndisuio_notification_deinit(drv);
#endif /* _WIN32_WCE */

	eloop_cancel_timeout(wpa_driver_ndis_scan_timeout, drv, drv->ctx);
	eloop_cancel_timeout(wpa_driver_ndis_poll_timeout, drv, NULL);
	wpa_driver_ndis_flush_pmkid(drv);
	wpa_driver_ndis_disconnect(drv);
	if (wpa_driver_ndis_radio_off(drv) < 0) {
		wpa_printf(MSG_DEBUG, "NDIS: failed to disassociate and turn "
			   "radio off");
	}

	wpa_driver_ndis_adapter_close(drv);

	if (drv->wzc_disabled)
		wpa_driver_ndis_set_wzc(drv, 1);

#ifdef _WIN32_WCE
	os_free(drv->adapter_name);
#endif /* _WIN32_WCE */
	os_free(drv->adapter_desc);
	os_free(drv);
}