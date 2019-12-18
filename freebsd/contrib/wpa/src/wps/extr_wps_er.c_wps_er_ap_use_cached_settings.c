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
struct wps_er_ap_settings {int /*<<< orphan*/  ap_settings; } ;
struct wps_er_ap {int /*<<< orphan*/ * ap_settings; int /*<<< orphan*/  uuid; int /*<<< orphan*/  er; } ;
struct wps_er {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/ * os_memdup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wps_er_ap_settings* wps_er_ap_get_settings (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wps_er_ap_use_cached_settings(struct wps_er *er,
					 struct wps_er_ap *ap)
{
	struct wps_er_ap_settings *s;

	if (ap->ap_settings)
		return 0;

	s = wps_er_ap_get_settings(ap->er, ap->uuid);
	if (!s)
		return -1;

	ap->ap_settings = os_memdup(&s->ap_settings, sizeof(*ap->ap_settings));
	if (ap->ap_settings == NULL)
		return -1;

	wpa_printf(MSG_DEBUG, "WPS ER: Use cached AP settings");
	return 0;
}