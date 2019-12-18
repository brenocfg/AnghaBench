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
struct teap_tlv_result {void* status; void* length; void* tlv_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int TEAP_STATUS_FAILURE ; 
 int TEAP_STATUS_SUCCESS ; 
 int TEAP_TLV_INTERMEDIATE_RESULT ; 
 int TEAP_TLV_MANDATORY ; 
 int TEAP_TLV_RESULT ; 
 void* host_to_be16 (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 struct teap_tlv_result* wpabuf_put (struct wpabuf*,int) ; 

struct wpabuf * eap_teap_tlv_result(int status, int intermediate)
{
	struct wpabuf *buf;
	struct teap_tlv_result *result;

	if (status != TEAP_STATUS_FAILURE && status != TEAP_STATUS_SUCCESS)
		return NULL;

	buf = wpabuf_alloc(sizeof(*result));
	if (!buf)
		return NULL;
	wpa_printf(MSG_DEBUG, "EAP-TEAP: Add %sResult TLV(status=%s)",
		   intermediate ? "Intermediate-" : "",
		   status == TEAP_STATUS_SUCCESS ? "Success" : "Failure");
	result = wpabuf_put(buf, sizeof(*result));
	result->tlv_type = host_to_be16(TEAP_TLV_MANDATORY |
					(intermediate ?
					 TEAP_TLV_INTERMEDIATE_RESULT :
					 TEAP_TLV_RESULT));
	result->length = host_to_be16(2);
	result->status = host_to_be16(status);
	return buf;
}