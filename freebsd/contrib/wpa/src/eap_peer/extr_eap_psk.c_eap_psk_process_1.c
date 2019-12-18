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
struct eap_psk_hdr_2 {int /*<<< orphan*/ * mac_p; int /*<<< orphan*/ * rand_p; int /*<<< orphan*/ * rand_s; int /*<<< orphan*/  flags; } ;
struct eap_psk_hdr_1 {int /*<<< orphan*/ * rand_s; int /*<<< orphan*/  flags; } ;
struct eap_psk_data {size_t id_s_len; int id_p_len; int /*<<< orphan*/  state; int /*<<< orphan*/ * id_p; int /*<<< orphan*/  ak; int /*<<< orphan*/ * rand_p; int /*<<< orphan*/ * id_s; int /*<<< orphan*/ * rand_s; } ;
struct eap_method_ret {void* ignore; int /*<<< orphan*/  decision; int /*<<< orphan*/  methodState; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECISION_FAIL ; 
 int /*<<< orphan*/  EAP_CODE_RESPONSE ; 
 int /*<<< orphan*/  EAP_PSK_FLAGS_GET_T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EAP_PSK_FLAGS_SET_T (int) ; 
 int EAP_PSK_MAC_LEN ; 
 int EAP_PSK_RAND_LEN ; 
 int /*<<< orphan*/  EAP_TYPE_PSK ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  METHOD_DONE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  PSK_MAC_SENT ; 
 void* TRUE ; 
 int /*<<< orphan*/  eap_get_id (struct wpabuf const*) ; 
 int /*<<< orphan*/ * eap_hdr_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf const*,size_t*) ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ omac1_aes_128 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * os_memdup (struct eap_psk_hdr_1 const*,size_t) ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 struct eap_psk_hdr_2* wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct wpabuf * eap_psk_process_1(struct eap_psk_data *data,
					 struct eap_method_ret *ret,
					 const struct wpabuf *reqData)
{
	const struct eap_psk_hdr_1 *hdr1;
	struct eap_psk_hdr_2 *hdr2;
	struct wpabuf *resp;
	u8 *buf, *pos;
	size_t buflen, len;
	const u8 *cpos;

	wpa_printf(MSG_DEBUG, "EAP-PSK: in INIT state");

	cpos = eap_hdr_validate(EAP_VENDOR_IETF, EAP_TYPE_PSK, reqData, &len);
	hdr1 = (const struct eap_psk_hdr_1 *) cpos;
	if (cpos == NULL || len < sizeof(*hdr1)) {
		wpa_printf(MSG_INFO, "EAP-PSK: Invalid first message "
			   "length (%lu; expected %lu or more)",
			   (unsigned long) len,
			   (unsigned long) sizeof(*hdr1));
		ret->ignore = TRUE;
		return NULL;
	}
	wpa_printf(MSG_DEBUG, "EAP-PSK: Flags=0x%x", hdr1->flags);
	if (EAP_PSK_FLAGS_GET_T(hdr1->flags) != 0) {
		wpa_printf(MSG_INFO, "EAP-PSK: Unexpected T=%d (expected 0)",
			   EAP_PSK_FLAGS_GET_T(hdr1->flags));
		ret->methodState = METHOD_DONE;
		ret->decision = DECISION_FAIL;
		return NULL;
	}
	wpa_hexdump(MSG_DEBUG, "EAP-PSK: RAND_S", hdr1->rand_s,
		    EAP_PSK_RAND_LEN);
	os_memcpy(data->rand_s, hdr1->rand_s, EAP_PSK_RAND_LEN);
	os_free(data->id_s);
	data->id_s_len = len - sizeof(*hdr1);
	data->id_s = os_memdup(hdr1 + 1, data->id_s_len);
	if (data->id_s == NULL) {
		wpa_printf(MSG_ERROR, "EAP-PSK: Failed to allocate memory for "
			   "ID_S (len=%lu)", (unsigned long) data->id_s_len);
		ret->ignore = TRUE;
		return NULL;
	}
	wpa_hexdump_ascii(MSG_DEBUG, "EAP-PSK: ID_S",
			  data->id_s, data->id_s_len);

	if (random_get_bytes(data->rand_p, EAP_PSK_RAND_LEN)) {
		wpa_printf(MSG_ERROR, "EAP-PSK: Failed to get random data");
		ret->ignore = TRUE;
		return NULL;
	}

	resp = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_PSK,
			     sizeof(*hdr2) + data->id_p_len, EAP_CODE_RESPONSE,
			     eap_get_id(reqData));
	if (resp == NULL)
		return NULL;
	hdr2 = wpabuf_put(resp, sizeof(*hdr2));
	hdr2->flags = EAP_PSK_FLAGS_SET_T(1); /* T=1 */
	os_memcpy(hdr2->rand_s, hdr1->rand_s, EAP_PSK_RAND_LEN);
	os_memcpy(hdr2->rand_p, data->rand_p, EAP_PSK_RAND_LEN);
	wpabuf_put_data(resp, data->id_p, data->id_p_len);
	/* MAC_P = OMAC1-AES-128(AK, ID_P||ID_S||RAND_S||RAND_P) */
	buflen = data->id_p_len + data->id_s_len + 2 * EAP_PSK_RAND_LEN;
	buf = os_malloc(buflen);
	if (buf == NULL) {
		wpabuf_free(resp);
		return NULL;
	}
	os_memcpy(buf, data->id_p, data->id_p_len);
	pos = buf + data->id_p_len;
	os_memcpy(pos, data->id_s, data->id_s_len);
	pos += data->id_s_len;
	os_memcpy(pos, hdr1->rand_s, EAP_PSK_RAND_LEN);
	pos += EAP_PSK_RAND_LEN;
	os_memcpy(pos, data->rand_p, EAP_PSK_RAND_LEN);
	if (omac1_aes_128(data->ak, buf, buflen, hdr2->mac_p)) {
		os_free(buf);
		wpabuf_free(resp);
		return NULL;
	}
	os_free(buf);
	wpa_hexdump(MSG_DEBUG, "EAP-PSK: RAND_P", hdr2->rand_p,
		    EAP_PSK_RAND_LEN);
	wpa_hexdump(MSG_DEBUG, "EAP-PSK: MAC_P", hdr2->mac_p, EAP_PSK_MAC_LEN);
	wpa_hexdump_ascii(MSG_DEBUG, "EAP-PSK: ID_P",
			  data->id_p, data->id_p_len);

	data->state = PSK_MAC_SENT;

	return resp;
}