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
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct eap_tls_data {scalar_t__ eap_type; } ;
struct eap_sm {int dummy; } ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 scalar_t__ EAP_UNAUTH_TLS_TYPE ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 scalar_t__ EAP_VENDOR_TYPE_UNAUTH_TLS ; 
 int /*<<< orphan*/  EAP_VENDOR_UNAUTH_TLS ; 
 int /*<<< orphan*/  EAP_VENDOR_WFA_NEW ; 
 scalar_t__ EAP_VENDOR_WFA_UNAUTH_TLS ; 
 scalar_t__ EAP_WFA_UNAUTH_TLS_TYPE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * eap_hdr_validate (int /*<<< orphan*/ ,scalar_t__,struct wpabuf*,size_t*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static Boolean eap_tls_check(struct eap_sm *sm, void *priv,
			     struct wpabuf *respData)
{
	struct eap_tls_data *data = priv;
	const u8 *pos;
	size_t len;

	if (data->eap_type == EAP_UNAUTH_TLS_TYPE)
		pos = eap_hdr_validate(EAP_VENDOR_UNAUTH_TLS,
				       EAP_VENDOR_TYPE_UNAUTH_TLS, respData,
				       &len);
	else if (data->eap_type == EAP_WFA_UNAUTH_TLS_TYPE)
		pos = eap_hdr_validate(EAP_VENDOR_WFA_NEW,
				       EAP_VENDOR_WFA_UNAUTH_TLS, respData,
				       &len);
	else
		pos = eap_hdr_validate(EAP_VENDOR_IETF, data->eap_type,
				       respData, &len);
	if (pos == NULL || len < 1) {
		wpa_printf(MSG_INFO, "EAP-TLS: Invalid frame");
		return TRUE;
	}

	return FALSE;
}