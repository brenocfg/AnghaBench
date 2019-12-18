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
typedef  enum teap_tlv_types { ____Placeholder_teap_tlv_types } teap_tlv_types ;

/* Variables and functions */
#define  TEAP_TLV_AUTHORITY_ID 144 
#define  TEAP_TLV_BASIC_PASSWORD_AUTH_REQ 143 
#define  TEAP_TLV_BASIC_PASSWORD_AUTH_RESP 142 
#define  TEAP_TLV_CHANNEL_BINDING 141 
#define  TEAP_TLV_CRYPTO_BINDING 140 
#define  TEAP_TLV_EAP_PAYLOAD 139 
#define  TEAP_TLV_ERROR 138 
#define  TEAP_TLV_IDENTITY_TYPE 137 
#define  TEAP_TLV_INTERMEDIATE_RESULT 136 
#define  TEAP_TLV_NAK 135 
#define  TEAP_TLV_PAC 134 
#define  TEAP_TLV_PKCS10 133 
#define  TEAP_TLV_PKCS7 132 
#define  TEAP_TLV_REQUEST_ACTION 131 
#define  TEAP_TLV_RESULT 130 
#define  TEAP_TLV_TRUSTED_SERVER_ROOT 129 
#define  TEAP_TLV_VENDOR_SPECIFIC 128 

const char * eap_teap_tlv_type_str(enum teap_tlv_types type)
{
	switch (type) {
	case TEAP_TLV_AUTHORITY_ID:
		return "Authority-ID";
	case TEAP_TLV_IDENTITY_TYPE:
		return "Identity-Type";
	case TEAP_TLV_RESULT:
		return "Result";
	case TEAP_TLV_NAK:
		return "NAK";
	case TEAP_TLV_ERROR:
		return "Error";
	case TEAP_TLV_CHANNEL_BINDING:
		return "Channel-Binding";
	case TEAP_TLV_VENDOR_SPECIFIC:
		return "Vendor-Specific";
	case TEAP_TLV_REQUEST_ACTION:
		return "Request-Action";
	case TEAP_TLV_EAP_PAYLOAD:
		return "EAP-Payload";
	case TEAP_TLV_INTERMEDIATE_RESULT:
		return "Intermediate-Result";
	case TEAP_TLV_PAC:
		return "PAC";
	case TEAP_TLV_CRYPTO_BINDING:
		return "Crypto-Binding";
	case TEAP_TLV_BASIC_PASSWORD_AUTH_REQ:
		return "Basic-Password-Auth-Req";
	case TEAP_TLV_BASIC_PASSWORD_AUTH_RESP:
		return "Basic-Password-Auth-Resp";
	case TEAP_TLV_PKCS7:
		return "PKCS#7";
	case TEAP_TLV_PKCS10:
		return "PKCS#10";
	case TEAP_TLV_TRUSTED_SERVER_ROOT:
		return "Trusted-Server-Root";
	}

	return "?";
}