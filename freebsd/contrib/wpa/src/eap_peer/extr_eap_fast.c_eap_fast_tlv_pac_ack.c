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
struct eap_tlv_result_tlv {int dummy; } ;
struct eap_tlv_pac_ack_tlv {void* result; void* pac_len; void* pac_type; void* length; void* tlv_type; } ;
struct eap_tlv_hdr {int dummy; } ;

/* Variables and functions */
 int EAP_TLV_PAC_TLV ; 
 int EAP_TLV_RESULT_SUCCESS ; 
 int EAP_TLV_TYPE_MANDATORY ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int PAC_TYPE_PAC_ACKNOWLEDGEMENT ; 
 void* host_to_be16 (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 struct eap_tlv_pac_ack_tlv* wpabuf_put (struct wpabuf*,int) ; 

__attribute__((used)) static struct wpabuf * eap_fast_tlv_pac_ack(void)
{
	struct wpabuf *buf;
	struct eap_tlv_result_tlv *res;
	struct eap_tlv_pac_ack_tlv *ack;

	buf = wpabuf_alloc(sizeof(*res) + sizeof(*ack));
	if (buf == NULL)
		return NULL;

	wpa_printf(MSG_DEBUG, "EAP-FAST: Add PAC TLV (ack)");
	ack = wpabuf_put(buf, sizeof(*ack));
	ack->tlv_type = host_to_be16(EAP_TLV_PAC_TLV |
				     EAP_TLV_TYPE_MANDATORY);
	ack->length = host_to_be16(sizeof(*ack) - sizeof(struct eap_tlv_hdr));
	ack->pac_type = host_to_be16(PAC_TYPE_PAC_ACKNOWLEDGEMENT);
	ack->pac_len = host_to_be16(2);
	ack->result = host_to_be16(EAP_TLV_RESULT_SUCCESS);

	return buf;
}