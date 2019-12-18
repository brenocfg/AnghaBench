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
struct wpa_supplicant {int dummy; } ;
struct nai_realm_eap {scalar_t__ method; scalar_t__ inner_method; scalar_t__ inner_non_eap; } ;

/* Variables and functions */
 scalar_t__ EAP_TYPE_FAST ; 
 scalar_t__ EAP_TYPE_GTC ; 
 scalar_t__ EAP_TYPE_MSCHAPV2 ; 
 scalar_t__ EAP_TYPE_PEAP ; 
 scalar_t__ EAP_TYPE_TTLS ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ NAI_REALM_INNER_NON_EAP_CHAP ; 
 scalar_t__ NAI_REALM_INNER_NON_EAP_MSCHAP ; 
 scalar_t__ NAI_REALM_INNER_NON_EAP_MSCHAPV2 ; 
 scalar_t__ NAI_REALM_INNER_NON_EAP_PAP ; 
 int /*<<< orphan*/ * eap_get_name (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int nai_realm_cred_username(struct wpa_supplicant *wpa_s,
				   struct nai_realm_eap *eap)
{
	if (eap_get_name(EAP_VENDOR_IETF, eap->method) == NULL) {
		wpa_msg(wpa_s, MSG_DEBUG,
			"nai-realm-cred-username: EAP method not supported: %d",
			eap->method);
		return 0; /* method not supported */
	}

	if (eap->method != EAP_TYPE_TTLS && eap->method != EAP_TYPE_PEAP &&
	    eap->method != EAP_TYPE_FAST) {
		/* Only tunneled methods with username/password supported */
		wpa_msg(wpa_s, MSG_DEBUG,
			"nai-realm-cred-username: Method: %d is not TTLS, PEAP, or FAST",
			eap->method);
		return 0;
	}

	if (eap->method == EAP_TYPE_PEAP || eap->method == EAP_TYPE_FAST) {
		if (eap->inner_method &&
		    eap_get_name(EAP_VENDOR_IETF, eap->inner_method) == NULL) {
			wpa_msg(wpa_s, MSG_DEBUG,
				"nai-realm-cred-username: PEAP/FAST: Inner method not supported: %d",
				eap->inner_method);
			return 0;
		}
		if (!eap->inner_method &&
		    eap_get_name(EAP_VENDOR_IETF, EAP_TYPE_MSCHAPV2) == NULL) {
			wpa_msg(wpa_s, MSG_DEBUG,
				"nai-realm-cred-username: MSCHAPv2 not supported");
			return 0;
		}
	}

	if (eap->method == EAP_TYPE_TTLS) {
		if (eap->inner_method == 0 && eap->inner_non_eap == 0)
			return 1; /* Assume TTLS/MSCHAPv2 is used */
		if (eap->inner_method &&
		    eap_get_name(EAP_VENDOR_IETF, eap->inner_method) == NULL) {
			wpa_msg(wpa_s, MSG_DEBUG,
				"nai-realm-cred-username: TTLS, but inner not supported: %d",
				eap->inner_method);
			return 0;
		}
		if (eap->inner_non_eap &&
		    eap->inner_non_eap != NAI_REALM_INNER_NON_EAP_PAP &&
		    eap->inner_non_eap != NAI_REALM_INNER_NON_EAP_CHAP &&
		    eap->inner_non_eap != NAI_REALM_INNER_NON_EAP_MSCHAP &&
		    eap->inner_non_eap != NAI_REALM_INNER_NON_EAP_MSCHAPV2) {
			wpa_msg(wpa_s, MSG_DEBUG,
				"nai-realm-cred-username: TTLS, inner-non-eap not supported: %d",
				eap->inner_non_eap);
			return 0;
		}
	}

	if (eap->inner_method &&
	    eap->inner_method != EAP_TYPE_GTC &&
	    eap->inner_method != EAP_TYPE_MSCHAPV2) {
		wpa_msg(wpa_s, MSG_DEBUG,
			"nai-realm-cred-username: inner-method not GTC or MSCHAPv2: %d",
			eap->inner_method);
		return 0;
	}

	return 1;
}