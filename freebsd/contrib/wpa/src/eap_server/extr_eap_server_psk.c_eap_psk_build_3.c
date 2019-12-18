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
typedef  int u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int server_id_len; int* server_id; } ;
struct eap_psk_hdr_3 {int* rand_s; int /*<<< orphan*/  mac_s; int /*<<< orphan*/  flags; } ;
struct eap_psk_data {int* rand_s; int* rand_p; void* state; int /*<<< orphan*/  tek; int /*<<< orphan*/  emsk; int /*<<< orphan*/  msk; int /*<<< orphan*/  kdk; int /*<<< orphan*/  ak; } ;
typedef  int /*<<< orphan*/  nonce ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_REQUEST ; 
 int /*<<< orphan*/  EAP_EMSK_LEN ; 
 int /*<<< orphan*/  EAP_MSK_LEN ; 
 int /*<<< orphan*/  EAP_PSK_FLAGS_SET_T (int) ; 
 int EAP_PSK_RAND_LEN ; 
 int EAP_PSK_R_FLAG_DONE_SUCCESS ; 
 int /*<<< orphan*/  EAP_PSK_TEK_LEN ; 
 int /*<<< orphan*/  EAP_TYPE_PSK ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 void* FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 scalar_t__ aes_128_eax_encrypt (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,int,int*,int,int*) ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ eap_psk_derive_keys (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ omac1_aes_128 (int /*<<< orphan*/ ,int*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (int*) ; 
 int* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  os_memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 void* wpabuf_put (struct wpabuf*,int) ; 

__attribute__((used)) static struct wpabuf * eap_psk_build_3(struct eap_sm *sm,
				       struct eap_psk_data *data, u8 id)
{
	struct wpabuf *req;
	struct eap_psk_hdr_3 *psk;
	u8 *buf, *pchannel, nonce[16];
	size_t buflen;

	wpa_printf(MSG_DEBUG, "EAP-PSK: PSK-3 (sending)");

	req = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_PSK,
			    sizeof(*psk) + 4 + 16 + 1, EAP_CODE_REQUEST, id);
	if (req == NULL) {
		wpa_printf(MSG_ERROR, "EAP-PSK: Failed to allocate memory "
			   "request");
		data->state = FAILURE;
		return NULL;
	}

	psk = wpabuf_put(req, sizeof(*psk));
	psk->flags = EAP_PSK_FLAGS_SET_T(2); /* T=2 */
	os_memcpy(psk->rand_s, data->rand_s, EAP_PSK_RAND_LEN);

	/* MAC_S = OMAC1-AES-128(AK, ID_S||RAND_P) */
	buflen = sm->server_id_len + EAP_PSK_RAND_LEN;
	buf = os_malloc(buflen);
	if (buf == NULL)
		goto fail;

	os_memcpy(buf, sm->server_id, sm->server_id_len);
	os_memcpy(buf + sm->server_id_len, data->rand_p, EAP_PSK_RAND_LEN);
	if (omac1_aes_128(data->ak, buf, buflen, psk->mac_s)) {
		os_free(buf);
		goto fail;
	}
	os_free(buf);

	if (eap_psk_derive_keys(data->kdk, data->rand_p, data->tek, data->msk,
				data->emsk))
		goto fail;
	wpa_hexdump_key(MSG_DEBUG, "EAP-PSK: TEK", data->tek, EAP_PSK_TEK_LEN);
	wpa_hexdump_key(MSG_DEBUG, "EAP-PSK: MSK", data->msk, EAP_MSK_LEN);
	wpa_hexdump_key(MSG_DEBUG, "EAP-PSK: EMSK", data->emsk, EAP_EMSK_LEN);

	os_memset(nonce, 0, sizeof(nonce));
	pchannel = wpabuf_put(req, 4 + 16 + 1);
	os_memcpy(pchannel, nonce + 12, 4);
	os_memset(pchannel + 4, 0, 16); /* Tag */
	pchannel[4 + 16] = EAP_PSK_R_FLAG_DONE_SUCCESS << 6;
	wpa_hexdump(MSG_DEBUG, "EAP-PSK: PCHANNEL (plaintext)",
		    pchannel, 4 + 16 + 1);
	if (aes_128_eax_encrypt(data->tek, nonce, sizeof(nonce),
				wpabuf_head(req), 22,
				pchannel + 4 + 16, 1, pchannel + 4))
		goto fail;
	wpa_hexdump(MSG_DEBUG, "EAP-PSK: PCHANNEL (encrypted)",
		    pchannel, 4 + 16 + 1);

	return req;

fail:
	wpabuf_free(req);
	data->state = FAILURE;
	return NULL;
}