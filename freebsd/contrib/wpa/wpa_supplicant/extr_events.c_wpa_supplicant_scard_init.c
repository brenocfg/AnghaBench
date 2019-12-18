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
struct wpa_supplicant {int /*<<< orphan*/ * scard; int /*<<< orphan*/  eapol; int /*<<< orphan*/  wpa; TYPE_2__* conf; } ;
struct TYPE_3__ {struct eap_method_type* eap_methods; int /*<<< orphan*/ * pcsc; } ;
struct wpa_ssid {TYPE_1__ eap; } ;
struct eap_method_type {scalar_t__ vendor; scalar_t__ method; } ;
struct TYPE_4__ {int /*<<< orphan*/  pcsc_reader; scalar_t__ external_sim; } ;

/* Variables and functions */
 scalar_t__ EAP_TYPE_AKA ; 
 scalar_t__ EAP_TYPE_AKA_PRIME ; 
 scalar_t__ EAP_TYPE_NONE ; 
 scalar_t__ EAP_TYPE_SIM ; 
 scalar_t__ EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/ * eap_peer_get_eap_method (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  eapol_sm_register_scard_ctx (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * scard_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_sm_set_scard_ctx (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int wpa_supplicant_scard_init(struct wpa_supplicant *wpa_s,
			      struct wpa_ssid *ssid)
{
#ifdef IEEE8021X_EAPOL
#ifdef PCSC_FUNCS
	int aka = 0, sim = 0;

	if ((ssid != NULL && ssid->eap.pcsc == NULL) ||
	    wpa_s->scard != NULL || wpa_s->conf->external_sim)
		return 0;

	if (ssid == NULL || ssid->eap.eap_methods == NULL) {
		sim = 1;
		aka = 1;
	} else {
		struct eap_method_type *eap = ssid->eap.eap_methods;
		while (eap->vendor != EAP_VENDOR_IETF ||
		       eap->method != EAP_TYPE_NONE) {
			if (eap->vendor == EAP_VENDOR_IETF) {
				if (eap->method == EAP_TYPE_SIM)
					sim = 1;
				else if (eap->method == EAP_TYPE_AKA ||
					 eap->method == EAP_TYPE_AKA_PRIME)
					aka = 1;
			}
			eap++;
		}
	}

	if (eap_peer_get_eap_method(EAP_VENDOR_IETF, EAP_TYPE_SIM) == NULL)
		sim = 0;
	if (eap_peer_get_eap_method(EAP_VENDOR_IETF, EAP_TYPE_AKA) == NULL &&
	    eap_peer_get_eap_method(EAP_VENDOR_IETF, EAP_TYPE_AKA_PRIME) ==
	    NULL)
		aka = 0;

	if (!sim && !aka) {
		wpa_dbg(wpa_s, MSG_DEBUG, "Selected network is configured to "
			"use SIM, but neither EAP-SIM nor EAP-AKA are "
			"enabled");
		return 0;
	}

	wpa_dbg(wpa_s, MSG_DEBUG, "Selected network is configured to use SIM "
		"(sim=%d aka=%d) - initialize PCSC", sim, aka);

	wpa_s->scard = scard_init(wpa_s->conf->pcsc_reader);
	if (wpa_s->scard == NULL) {
		wpa_msg(wpa_s, MSG_WARNING, "Failed to initialize SIM "
			"(pcsc-lite)");
		return -1;
	}
	wpa_sm_set_scard_ctx(wpa_s->wpa, wpa_s->scard);
	eapol_sm_register_scard_ctx(wpa_s->eapol, wpa_s->scard);
#endif /* PCSC_FUNCS */
#endif /* IEEE8021X_EAPOL */

	return 0;
}