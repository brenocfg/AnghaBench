#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wps_er_ap {TYPE_1__* ap_settings; } ;
struct wps_er {int dummy; } ;
struct wps_credential {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * cred_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_free (TYPE_1__*) ; 
 TYPE_1__* os_memdup (struct wps_credential const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wps_er_ap* wps_er_ap_get (struct wps_er*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

int wps_er_set_config(struct wps_er *er, const u8 *uuid, const u8 *addr,
		      const struct wps_credential *cred)
{
	struct wps_er_ap *ap;

	if (er == NULL)
		return -1;

	ap = wps_er_ap_get(er, NULL, uuid, addr);
	if (ap == NULL) {
		wpa_printf(MSG_DEBUG, "WPS ER: AP not found for set config "
			   "request");
		return -1;
	}

	os_free(ap->ap_settings);
	ap->ap_settings = os_memdup(cred, sizeof(*cred));
	if (ap->ap_settings == NULL)
		return -1;
	ap->ap_settings->cred_attr = NULL;
	wpa_printf(MSG_DEBUG, "WPS ER: Updated local AP settings based set "
		   "config request");

	return 0;
}