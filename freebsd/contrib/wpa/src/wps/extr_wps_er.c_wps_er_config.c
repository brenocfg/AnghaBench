#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wps_er_ap {TYPE_2__* ap_settings; scalar_t__ wps; int /*<<< orphan*/ * uuid; } ;
struct wps_er {int skip_set_sel_reg; TYPE_1__* wps; } ;
struct wps_credential {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * cred_attr; } ;
struct TYPE_4__ {int /*<<< orphan*/  registrar; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_free (TYPE_2__*) ; 
 TYPE_2__* os_memdup (struct wps_credential const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wps_er_ap_config_m1 ; 
 struct wps_er_ap* wps_er_ap_get (struct wps_er*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ wps_er_send_get_device_info (struct wps_er_ap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_registrar_add_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 

int wps_er_config(struct wps_er *er, const u8 *uuid, const u8 *addr,
		  const u8 *pin, size_t pin_len,
		  const struct wps_credential *cred)
{
	struct wps_er_ap *ap;

	if (er == NULL)
		return -1;

	ap = wps_er_ap_get(er, NULL, uuid, addr);
	if (ap == NULL) {
		wpa_printf(MSG_DEBUG, "WPS ER: AP not found for config "
			   "request");
		return -1;
	}
	if (uuid == NULL)
		uuid = ap->uuid;
	if (ap->wps) {
		wpa_printf(MSG_DEBUG, "WPS ER: Pending operation ongoing "
			   "with the AP - cannot start config");
		return -1;
	}

	os_free(ap->ap_settings);
	ap->ap_settings = os_memdup(cred, sizeof(*cred));
	if (ap->ap_settings == NULL)
		return -1;
	ap->ap_settings->cred_attr = NULL;

	if (wps_er_send_get_device_info(ap, wps_er_ap_config_m1) < 0)
		return -1;

	er->skip_set_sel_reg = 1;
	wps_registrar_add_pin(er->wps->registrar, NULL, uuid, pin, pin_len, 0);
	er->skip_set_sel_reg = 0;

	return 0;
}