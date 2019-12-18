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
typedef  scalar_t__ u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int dummy; } ;
struct eap_psk_hdr_4 {int dummy; } ;
struct eap_psk_data {scalar_t__ state; int /*<<< orphan*/  tek; } ;
typedef  int /*<<< orphan*/  nonce ;

/* Variables and functions */
#define  EAP_PSK_R_FLAG_CONT 130 
#define  EAP_PSK_R_FLAG_DONE_FAILURE 129 
#define  EAP_PSK_R_FLAG_DONE_SUCCESS 128 
 int /*<<< orphan*/  EAP_TYPE_PSK ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 void* FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 scalar_t__ PSK_3 ; 
 scalar_t__ SUCCESS ; 
 scalar_t__ aes_128_eax_decrypt (int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ,int,scalar_t__*,size_t,scalar_t__ const*) ; 
 scalar_t__* eap_hdr_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf*,size_t*) ; 
 int /*<<< orphan*/  os_free (scalar_t__*) ; 
 int /*<<< orphan*/  os_memcpy (scalar_t__*,scalar_t__ const*,int) ; 
 scalar_t__* os_memdup (scalar_t__ const*,size_t) ; 
 int /*<<< orphan*/  os_memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,scalar_t__ const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 

__attribute__((used)) static void eap_psk_process_4(struct eap_sm *sm,
			      struct eap_psk_data *data,
			      struct wpabuf *respData)
{
	const struct eap_psk_hdr_4 *resp;
	u8 *decrypted, nonce[16];
	size_t left;
	const u8 *pos, *tag;

	if (data->state != PSK_3)
		return;

	wpa_printf(MSG_DEBUG, "EAP-PSK: Received PSK-4");

	pos = eap_hdr_validate(EAP_VENDOR_IETF, EAP_TYPE_PSK, respData, &left);
	if (pos == NULL || left < sizeof(*resp)) {
		wpa_printf(MSG_INFO, "EAP-PSK: Invalid frame");
		return;
	}
	resp = (const struct eap_psk_hdr_4 *) pos;
	pos = (const u8 *) (resp + 1);
	left -= sizeof(*resp);

	wpa_hexdump(MSG_MSGDUMP, "EAP-PSK: Encrypted PCHANNEL", pos, left);

	if (left < 4 + 16 + 1) {
		wpa_printf(MSG_INFO, "EAP-PSK: Too short PCHANNEL data in "
			   "PSK-4 (len=%lu, expected 21)",
			   (unsigned long) left);
		return;
	}

	if (pos[0] == 0 && pos[1] == 0 && pos[2] == 0 && pos[3] == 0) {
		wpa_printf(MSG_DEBUG, "EAP-PSK: Nonce did not increase");
		return;
	}

	os_memset(nonce, 0, 12);
	os_memcpy(nonce + 12, pos, 4);
	pos += 4;
	left -= 4;
	tag = pos;
	pos += 16;
	left -= 16;

	decrypted = os_memdup(pos, left);
	if (decrypted == NULL)
		return;

	if (aes_128_eax_decrypt(data->tek, nonce, sizeof(nonce),
				wpabuf_head(respData), 22, decrypted, left,
				tag)) {
		wpa_printf(MSG_WARNING, "EAP-PSK: PCHANNEL decryption failed");
		os_free(decrypted);
		data->state = FAILURE;
		return;
	}
	wpa_hexdump(MSG_DEBUG, "EAP-PSK: Decrypted PCHANNEL message",
		    decrypted, left);

	/* Verify R flag */
	switch (decrypted[0] >> 6) {
	case EAP_PSK_R_FLAG_CONT:
		wpa_printf(MSG_DEBUG, "EAP-PSK: R flag - CONT - unsupported");
		data->state = FAILURE;
		break;
	case EAP_PSK_R_FLAG_DONE_SUCCESS:
		wpa_printf(MSG_DEBUG, "EAP-PSK: R flag - DONE_SUCCESS");
		data->state = SUCCESS;
		break;
	case EAP_PSK_R_FLAG_DONE_FAILURE:
		wpa_printf(MSG_DEBUG, "EAP-PSK: R flag - DONE_FAILURE");
		data->state = FAILURE;
		break;
	}
	os_free(decrypted);
}