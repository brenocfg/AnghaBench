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
typedef  int u16 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int dummy; } ;
struct eap_peap_data {scalar_t__ crypto_binding; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_RESPONSE ; 
 int EAP_TLV_RESULT_TLV ; 
 int /*<<< orphan*/  EAP_TYPE_TLV ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 scalar_t__ NO_BINDING ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int) ; 
 scalar_t__ eap_tlv_add_cryptobinding (struct eap_sm*,struct eap_peap_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_clear_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

__attribute__((used)) static struct wpabuf * eap_tlv_build_result(struct eap_sm *sm,
					    struct eap_peap_data *data,
					    int crypto_tlv_used,
					    int id, u16 status)
{
	struct wpabuf *msg;
	size_t len;

	if (data->crypto_binding == NO_BINDING)
		crypto_tlv_used = 0;

	len = 6;
	if (crypto_tlv_used)
		len += 60; /* Cryptobinding TLV */
	msg = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_TLV, len,
			    EAP_CODE_RESPONSE, id);
	if (msg == NULL)
		return NULL;

	wpabuf_put_u8(msg, 0x80); /* Mandatory */
	wpabuf_put_u8(msg, EAP_TLV_RESULT_TLV);
	wpabuf_put_be16(msg, 2); /* Length */
	wpabuf_put_be16(msg, status); /* Status */

	if (crypto_tlv_used && eap_tlv_add_cryptobinding(sm, data, msg)) {
		wpabuf_clear_free(msg);
		return NULL;
	}

	return msg;
}