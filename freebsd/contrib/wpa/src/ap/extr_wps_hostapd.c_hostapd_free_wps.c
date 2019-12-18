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
struct TYPE_2__ {int /*<<< orphan*/ * vendor_ext; } ;
struct wps_context {int /*<<< orphan*/  dh_privkey; int /*<<< orphan*/  dh_pubkey; struct wps_context* network_key; TYPE_1__ dev; } ;

/* Variables and functions */
 int MAX_WPS_VENDOR_EXTENSIONS ; 
 int /*<<< orphan*/  hostapd_wps_nfc_clear (struct wps_context*) ; 
 int /*<<< orphan*/  os_free (struct wps_context*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_device_data_free (TYPE_1__*) ; 

__attribute__((used)) static void hostapd_free_wps(struct wps_context *wps)
{
	int i;

	for (i = 0; i < MAX_WPS_VENDOR_EXTENSIONS; i++)
		wpabuf_free(wps->dev.vendor_ext[i]);
	wps_device_data_free(&wps->dev);
	os_free(wps->network_key);
	hostapd_wps_nfc_clear(wps);
	wpabuf_free(wps->dh_pubkey);
	wpabuf_free(wps->dh_privkey);
	os_free(wps);
}