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
struct teap_tlv_nak {void* nak_type; int /*<<< orphan*/  vendor_id; void* length; void* tlv_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int TEAP_TLV_MANDATORY ; 
 int TEAP_TLV_NAK ; 
 void* host_to_be16 (int) ; 
 int /*<<< orphan*/  host_to_be32 (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 struct teap_tlv_nak* wpabuf_put (struct wpabuf*,int) ; 

__attribute__((used)) static struct wpabuf * eap_teap_tlv_nak(int vendor_id, int tlv_type)
{
	struct wpabuf *buf;
	struct teap_tlv_nak *nak;

	wpa_printf(MSG_DEBUG,
		   "EAP-TEAP: Add NAK TLV (Vendor-Id %u NAK-Type %u)",
		   vendor_id, tlv_type);
	buf = wpabuf_alloc(sizeof(*nak));
	if (!buf)
		return NULL;
	nak = wpabuf_put(buf, sizeof(*nak));
	nak->tlv_type = host_to_be16(TEAP_TLV_MANDATORY | TEAP_TLV_NAK);
	nak->length = host_to_be16(6);
	nak->vendor_id = host_to_be32(vendor_id);
	nak->nak_type = host_to_be16(tlv_type);
	return buf;
}