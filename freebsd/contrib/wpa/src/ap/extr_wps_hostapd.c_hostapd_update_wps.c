#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hostapd_data {TYPE_2__* wps; TYPE_1__* conf; } ;
struct TYPE_4__ {int /*<<< orphan*/  registrar; int /*<<< orphan*/  upc; int /*<<< orphan*/  model_url; int /*<<< orphan*/  model_description; int /*<<< orphan*/  manufacturer_url; int /*<<< orphan*/  friendly_name; } ;
struct TYPE_3__ {scalar_t__ wps_state; int /*<<< orphan*/  upc; int /*<<< orphan*/  model_url; int /*<<< orphan*/  model_description; int /*<<< orphan*/  manufacturer_url; int /*<<< orphan*/  friendly_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  hostapd_deinit_wps (struct hostapd_data*) ; 
 int /*<<< orphan*/  hostapd_wps_set_vendor_ext (struct hostapd_data*,TYPE_2__*) ; 
 int /*<<< orphan*/  wps_registrar_update_ie (int /*<<< orphan*/ ) ; 

void hostapd_update_wps(struct hostapd_data *hapd)
{
	if (hapd->wps == NULL)
		return;

#ifdef CONFIG_WPS_UPNP
	hapd->wps->friendly_name = hapd->conf->friendly_name;
	hapd->wps->manufacturer_url = hapd->conf->manufacturer_url;
	hapd->wps->model_description = hapd->conf->model_description;
	hapd->wps->model_url = hapd->conf->model_url;
	hapd->wps->upc = hapd->conf->upc;
#endif /* CONFIG_WPS_UPNP */

	hostapd_wps_set_vendor_ext(hapd, hapd->wps);

	if (hapd->conf->wps_state)
		wps_registrar_update_ie(hapd->wps->registrar);
	else
		hostapd_deinit_wps(hapd);
}