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
struct hostapd_data {int /*<<< orphan*/ * eapol_auth; TYPE_1__* conf; scalar_t__ drv_priv; scalar_t__ driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  iface; scalar_t__ wpa; scalar_t__ ieee802_1x; } ;

/* Variables and functions */
 int /*<<< orphan*/  eapol_auth_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct hostapd_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hostapd_set_drv_ieee8021x (struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee802_1x_erp_flush (struct hostapd_data*) ; 
 int /*<<< orphan*/  ieee802_1x_rekey ; 

void ieee802_1x_deinit(struct hostapd_data *hapd)
{
	eloop_cancel_timeout(ieee802_1x_rekey, hapd, NULL);

	if (hapd->driver && hapd->drv_priv &&
	    (hapd->conf->ieee802_1x || hapd->conf->wpa))
		hostapd_set_drv_ieee8021x(hapd, hapd->conf->iface, 0);

	eapol_auth_deinit(hapd->eapol_auth);
	hapd->eapol_auth = NULL;

	ieee802_1x_erp_flush(hapd);
}