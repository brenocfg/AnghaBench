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
struct teap_tlv_result {int dummy; } ;
struct teap_tlv_pac_ack {void* result; void* pac_len; void* pac_type; void* length; void* tlv_type; } ;
struct teap_tlv_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int PAC_TYPE_PAC_ACKNOWLEDGEMENT ; 
 int TEAP_STATUS_SUCCESS ; 
 int TEAP_TLV_MANDATORY ; 
 int TEAP_TLV_PAC ; 
 void* host_to_be16 (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 struct teap_tlv_pac_ack* wpabuf_put (struct wpabuf*,int) ; 

__attribute__((used)) static struct wpabuf * eap_teap_tlv_pac_ack(void)
{
	struct wpabuf *buf;
	struct teap_tlv_result *res;
	struct teap_tlv_pac_ack *ack;

	buf = wpabuf_alloc(sizeof(*res) + sizeof(*ack));
	if (!buf)
		return NULL;

	wpa_printf(MSG_DEBUG, "EAP-TEAP: Add PAC TLV (ack)");
	ack = wpabuf_put(buf, sizeof(*ack));
	ack->tlv_type = host_to_be16(TEAP_TLV_PAC | TEAP_TLV_MANDATORY);
	ack->length = host_to_be16(sizeof(*ack) - sizeof(struct teap_tlv_hdr));
	ack->pac_type = host_to_be16(PAC_TYPE_PAC_ACKNOWLEDGEMENT);
	ack->pac_len = host_to_be16(2);
	ack->result = host_to_be16(TEAP_STATUS_SUCCESS);

	return buf;
}