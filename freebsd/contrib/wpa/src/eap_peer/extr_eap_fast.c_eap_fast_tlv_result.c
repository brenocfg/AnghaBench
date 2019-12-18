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
struct eap_tlv_intermediate_result_tlv {void* status; void* length; void* tlv_type; } ;

/* Variables and functions */
 int EAP_TLV_INTERMEDIATE_RESULT_TLV ; 
 int EAP_TLV_RESULT_TLV ; 
 int EAP_TLV_TYPE_MANDATORY ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 void* host_to_be16 (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*,int) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 struct eap_tlv_intermediate_result_tlv* wpabuf_put (struct wpabuf*,int) ; 

__attribute__((used)) static struct wpabuf * eap_fast_tlv_result(int status, int intermediate)
{
	struct wpabuf *buf;
	struct eap_tlv_intermediate_result_tlv *result;
	buf = wpabuf_alloc(sizeof(*result));
	if (buf == NULL)
		return NULL;
	wpa_printf(MSG_DEBUG, "EAP-FAST: Add %sResult TLV(status=%d)",
		   intermediate ? "Intermediate " : "", status);
	result = wpabuf_put(buf, sizeof(*result));
	result->tlv_type = host_to_be16(EAP_TLV_TYPE_MANDATORY |
					(intermediate ?
					 EAP_TLV_INTERMEDIATE_RESULT_TLV :
					 EAP_TLV_RESULT_TLV));
	result->length = host_to_be16(2);
	result->status = host_to_be16(status);
	return buf;
}