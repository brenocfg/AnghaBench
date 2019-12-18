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
struct teap_tlv_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int TEAP_TLV_EAP_PAYLOAD ; 
 int TEAP_TLV_MANDATORY ; 
 int /*<<< orphan*/  eap_teap_put_tlv_buf (struct wpabuf*,int,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__ wpabuf_len (struct wpabuf*) ; 

struct wpabuf * eap_teap_tlv_eap_payload(struct wpabuf *buf)
{
	struct wpabuf *e;

	if (!buf)
		return NULL;

	/* Encapsulate EAP packet in EAP-Payload TLV */
	wpa_printf(MSG_DEBUG, "EAP-TEAP: Add EAP-Payload TLV");
	e = wpabuf_alloc(sizeof(struct teap_tlv_hdr) + wpabuf_len(buf));
	if (!e) {
		wpa_printf(MSG_ERROR,
			   "EAP-TEAP: Failed to allocate memory for TLV encapsulation");
		wpabuf_free(buf);
		return NULL;
	}
	eap_teap_put_tlv_buf(e, TEAP_TLV_MANDATORY | TEAP_TLV_EAP_PAYLOAD, buf);
	wpabuf_free(buf);

	/* TODO: followed by optional TLVs associated with the EAP packet */

	return e;
}