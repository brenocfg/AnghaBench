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
struct nai_realm_eap {scalar_t__ method; } ;

/* Variables and functions */
 scalar_t__ EAP_TYPE_TLS ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/ * eap_get_name (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int nai_realm_cred_cert(struct wpa_supplicant *wpa_s,
			       struct nai_realm_eap *eap)
{
	if (eap_get_name(EAP_VENDOR_IETF, eap->method) == NULL) {
		wpa_msg(wpa_s, MSG_DEBUG,
			"nai-realm-cred-cert: Method not supported: %d",
			eap->method);
		return 0; /* method not supported */
	}

	if (eap->method != EAP_TYPE_TLS) {
		/* Only EAP-TLS supported for credential authentication */
		wpa_msg(wpa_s, MSG_DEBUG,
			"nai-realm-cred-cert: Method not TLS: %d",
			eap->method);
		return 0;
	}

	return 1;
}