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
struct pac_tlv_hdr {int dummy; } ;

/* Variables and functions */
 int EAP_TLV_EAP_PAYLOAD_TLV ; 
 int EAP_TLV_TYPE_MANDATORY ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eap_fast_put_tlv_buf (struct wpabuf*,int,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__ wpabuf_len (struct wpabuf*) ; 

struct wpabuf * eap_fast_tlv_eap_payload(struct wpabuf *buf)
{
	struct wpabuf *e;

	if (buf == NULL)
		return NULL;

	/* Encapsulate EAP packet in EAP-Payload TLV */
	wpa_printf(MSG_DEBUG, "EAP-FAST: Add EAP-Payload TLV");
	e = wpabuf_alloc(sizeof(struct pac_tlv_hdr) + wpabuf_len(buf));
	if (e == NULL) {
		wpa_printf(MSG_DEBUG, "EAP-FAST: Failed to allocate memory "
			   "for TLV encapsulation");
		wpabuf_free(buf);
		return NULL;
	}
	eap_fast_put_tlv_buf(e,
			     EAP_TLV_TYPE_MANDATORY | EAP_TLV_EAP_PAYLOAD_TLV,
			     buf);
	wpabuf_free(buf);
	return e;
}