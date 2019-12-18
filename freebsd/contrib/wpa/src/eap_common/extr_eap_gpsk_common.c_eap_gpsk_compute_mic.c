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

/* Variables and functions */
#define  EAP_GPSK_CIPHER_AES 129 
#define  EAP_GPSK_CIPHER_SHA256 128 
 int EAP_GPSK_VENDOR_IETF ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int eap_gpsk_compute_mic_aes (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int hmac_sha256 (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int eap_gpsk_compute_mic(const u8 *sk, size_t sk_len, int vendor,
			 int specifier, const u8 *data, size_t len, u8 *mic)
{
	int ret;

	if (vendor != EAP_GPSK_VENDOR_IETF)
		return -1;

	switch (specifier) {
	case EAP_GPSK_CIPHER_AES:
		ret = eap_gpsk_compute_mic_aes(sk, sk_len, data, len, mic);
		break;
#ifdef EAP_GPSK_SHA256
	case EAP_GPSK_CIPHER_SHA256:
		ret = hmac_sha256(sk, sk_len, data, len, mic);
		break;
#endif /* EAP_GPSK_SHA256 */
	default:
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Unknown cipher %d:%d used in "
			   "MIC computation", vendor, specifier);
		ret = -1;
		break;
	}

	if (ret)
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Could not compute MIC");

	return ret;
}