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
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct eap_gpsk_data {int /*<<< orphan*/  specifier; int /*<<< orphan*/  vendor; int /*<<< orphan*/  sk_len; int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_RESPONSE ; 
 int /*<<< orphan*/  EAP_GPSK_OPCODE_GPSK_4 ; 
 int /*<<< orphan*/  EAP_TYPE_GPSK ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ eap_gpsk_compute_mic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 size_t eap_gpsk_mic_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_gpsk_state (struct eap_gpsk_data*,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/ * wpabuf_put (struct wpabuf*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpabuf * eap_gpsk_send_gpsk_4(struct eap_gpsk_data *data,
					    u8 identifier)
{
	struct wpabuf *resp;
	u8 *rpos, *start;
	size_t mlen;

	wpa_printf(MSG_DEBUG, "EAP-GPSK: Sending Response/GPSK-4");

	mlen = eap_gpsk_mic_len(data->vendor, data->specifier);

	resp = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_GPSK, 1 + 2 + mlen,
			     EAP_CODE_RESPONSE, identifier);
	if (resp == NULL)
		return NULL;

	wpabuf_put_u8(resp, EAP_GPSK_OPCODE_GPSK_4);
	start = wpabuf_put(resp, 0);

	/* No PD_Payload_3 */
	wpabuf_put_be16(resp, 0);

	rpos = wpabuf_put(resp, mlen);
	if (eap_gpsk_compute_mic(data->sk, data->sk_len, data->vendor,
				 data->specifier, start, rpos - start, rpos) <
	    0) {
		eap_gpsk_state(data, FAILURE);
		wpabuf_free(resp);
		return NULL;
	}

	return resp;
}