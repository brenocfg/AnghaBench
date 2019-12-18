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
struct teap_tlv_request_action {int /*<<< orphan*/  action; int /*<<< orphan*/  status; void* length; void* tlv_type; } ;
struct teap_tlv_hdr {void* length; void* tlv_type; } ;
struct teap_attr_pac_type {void* pac_type; void* length; void* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int PAC_TYPE_PAC_TYPE ; 
 int PAC_TYPE_TUNNEL_PAC ; 
 int /*<<< orphan*/  TEAP_REQUEST_ACTION_PROCESS_TLV ; 
 int /*<<< orphan*/  TEAP_STATUS_SUCCESS ; 
 int TEAP_TLV_PAC ; 
 int TEAP_TLV_REQUEST_ACTION ; 
 void* host_to_be16 (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 void* wpabuf_put (struct wpabuf*,int) ; 

__attribute__((used)) static struct wpabuf * eap_teap_pac_request(void)
{
	struct wpabuf *req;
	struct teap_tlv_request_action *act;
	struct teap_tlv_hdr *pac;
	struct teap_attr_pac_type *type;

	req = wpabuf_alloc(sizeof(*act) + sizeof(*pac) + sizeof(*type));
	if (!req)
		return NULL;

	wpa_printf(MSG_DEBUG, "EAP-TEAP: Add Request Action TLV (Process TLV)");
	act = wpabuf_put(req, sizeof(*act));
	act->tlv_type = host_to_be16(TEAP_TLV_REQUEST_ACTION);
	act->length = host_to_be16(2);
	act->status = TEAP_STATUS_SUCCESS;
	act->action = TEAP_REQUEST_ACTION_PROCESS_TLV;

	wpa_printf(MSG_DEBUG, "EAP-TEAP: Add PAC TLV (PAC-Type = Tunnel)");
	pac = wpabuf_put(req, sizeof(*pac));
	pac->tlv_type = host_to_be16(TEAP_TLV_PAC);
	pac->length = host_to_be16(sizeof(*type));

	type = wpabuf_put(req, sizeof(*type));
	type->type = host_to_be16(PAC_TYPE_PAC_TYPE);
	type->length = host_to_be16(2);
	type->pac_type = host_to_be16(PAC_TYPE_TUNNEL_PAC);

	return req;
}