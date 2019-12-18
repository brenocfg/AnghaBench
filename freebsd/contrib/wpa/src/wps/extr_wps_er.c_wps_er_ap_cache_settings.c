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
struct wps_er_ap_settings {int /*<<< orphan*/  ap_settings; int /*<<< orphan*/  list; int /*<<< orphan*/ * uuid; } ;
struct wps_er_ap {int /*<<< orphan*/ * ap_settings; int /*<<< orphan*/ * uuid; } ;
struct wps_er {int /*<<< orphan*/  ap_settings; } ;
struct wps_credential {int dummy; } ;
struct in_addr {int dummy; } ;

/* Variables and functions */
 int WPS_UUID_LEN ; 
 int /*<<< orphan*/  dl_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct wps_er_ap_settings* os_zalloc (int) ; 
 struct wps_er_ap* wps_er_ap_get (struct wps_er*,struct in_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct wps_er_ap_settings* wps_er_ap_get_settings (struct wps_er*,int /*<<< orphan*/ *) ; 

int wps_er_ap_cache_settings(struct wps_er *er, struct in_addr *addr)
{
	struct wps_er_ap *ap;
	struct wps_er_ap_settings *settings;

	ap = wps_er_ap_get(er, addr, NULL, NULL);
	if (ap == NULL || ap->ap_settings == NULL)
		return -1;

	settings = wps_er_ap_get_settings(er, ap->uuid);
	if (!settings) {
		settings = os_zalloc(sizeof(*settings));
		if (settings == NULL)
			return -1;
		os_memcpy(settings->uuid, ap->uuid, WPS_UUID_LEN);
		dl_list_add(&er->ap_settings, &settings->list);
	}
	os_memcpy(&settings->ap_settings, ap->ap_settings,
		  sizeof(struct wps_credential));

	return 0;
}