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
struct wpabuf {int dummy; } ;
struct eap_sm {scalar_t__ reqVendor; scalar_t__ reqVendorMethod; } ;
struct eap_method {scalar_t__ vendor; scalar_t__ method; struct eap_method* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_RESPONSE ; 
 int /*<<< orphan*/  EAP_TYPE_EXPANDED ; 
 scalar_t__ EAP_TYPE_NAK ; 
 scalar_t__ EAP_TYPE_NONE ; 
 scalar_t__ EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ eap_allowed_method (struct eap_sm*,scalar_t__,scalar_t__) ; 
 struct wpabuf* eap_msg_alloc (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  eap_update_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_put_be24 (struct wpabuf*,scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_put_be32 (struct wpabuf*,scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpabuf * eap_sm_build_expanded_nak(
	struct eap_sm *sm, int id, const struct eap_method *methods,
	size_t count)
{
	struct wpabuf *resp;
	int found = 0;
	const struct eap_method *m;

	wpa_printf(MSG_DEBUG, "EAP: Building expanded EAP-Nak");

	/* RFC 3748 - 5.3.2: Expanded Nak */
	resp = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_EXPANDED,
			     8 + 8 * (count + 1), EAP_CODE_RESPONSE, id);
	if (resp == NULL)
		return NULL;

	wpabuf_put_be24(resp, EAP_VENDOR_IETF);
	wpabuf_put_be32(resp, EAP_TYPE_NAK);

	for (m = methods; m; m = m->next) {
		if (sm->reqVendor == m->vendor &&
		    sm->reqVendorMethod == m->method)
			continue; /* do not allow the current method again */
		if (eap_allowed_method(sm, m->vendor, m->method)) {
			wpa_printf(MSG_DEBUG, "EAP: allowed type: "
				   "vendor=%u method=%u",
				   m->vendor, m->method);
			wpabuf_put_u8(resp, EAP_TYPE_EXPANDED);
			wpabuf_put_be24(resp, m->vendor);
			wpabuf_put_be32(resp, m->method);

			found++;
		}
	}
	if (!found) {
		wpa_printf(MSG_DEBUG, "EAP: no more allowed methods");
		wpabuf_put_u8(resp, EAP_TYPE_EXPANDED);
		wpabuf_put_be24(resp, EAP_VENDOR_IETF);
		wpabuf_put_be32(resp, EAP_TYPE_NONE);
	}

	eap_update_len(resp);

	return resp;
}