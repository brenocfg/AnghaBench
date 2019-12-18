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
 int MD5_MAC_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int SHA512_MAC_LEN ; 
#define  WPA_KEY_INFO_TYPE_AES_128_CMAC 139 
#define  WPA_KEY_INFO_TYPE_AKM_DEFINED 138 
#define  WPA_KEY_INFO_TYPE_HMAC_MD5_RC4 137 
#define  WPA_KEY_INFO_TYPE_HMAC_SHA1_AES 136 
#define  WPA_KEY_MGMT_DPP 135 
#define  WPA_KEY_MGMT_FT_IEEE8021X_SHA384 134 
#define  WPA_KEY_MGMT_FT_SAE 133 
#define  WPA_KEY_MGMT_IEEE8021X_SUITE_B 132 
#define  WPA_KEY_MGMT_IEEE8021X_SUITE_B_192 131 
#define  WPA_KEY_MGMT_OSEN 130 
#define  WPA_KEY_MGMT_OWE 129 
#define  WPA_KEY_MGMT_SAE 128 
 int hmac_md5 (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hmac_sha1 (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hmac_sha256 (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hmac_sha384 (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hmac_sha512 (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int omac1_aes_128 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int wpa_eapol_key_mic(const u8 *key, size_t key_len, int akmp, int ver,
		      const u8 *buf, size_t len, u8 *mic)
{
	u8 hash[SHA512_MAC_LEN];

	if (key_len == 0) {
		wpa_printf(MSG_DEBUG,
			   "WPA: KCK not set - cannot calculate MIC");
		return -1;
	}

	switch (ver) {
#ifndef CONFIG_FIPS
	case WPA_KEY_INFO_TYPE_HMAC_MD5_RC4:
		wpa_printf(MSG_DEBUG, "WPA: EAPOL-Key MIC using HMAC-MD5");
		return hmac_md5(key, key_len, buf, len, mic);
#endif /* CONFIG_FIPS */
	case WPA_KEY_INFO_TYPE_HMAC_SHA1_AES:
		wpa_printf(MSG_DEBUG, "WPA: EAPOL-Key MIC using HMAC-SHA1");
		if (hmac_sha1(key, key_len, buf, len, hash))
			return -1;
		os_memcpy(mic, hash, MD5_MAC_LEN);
		break;
#if defined(CONFIG_IEEE80211R) || defined(CONFIG_IEEE80211W)
	case WPA_KEY_INFO_TYPE_AES_128_CMAC:
		wpa_printf(MSG_DEBUG, "WPA: EAPOL-Key MIC using AES-CMAC");
		return omac1_aes_128(key, buf, len, mic);
#endif /* CONFIG_IEEE80211R || CONFIG_IEEE80211W */
	case WPA_KEY_INFO_TYPE_AKM_DEFINED:
		switch (akmp) {
#ifdef CONFIG_SAE
		case WPA_KEY_MGMT_SAE:
		case WPA_KEY_MGMT_FT_SAE:
			wpa_printf(MSG_DEBUG,
				   "WPA: EAPOL-Key MIC using AES-CMAC (AKM-defined - SAE)");
			return omac1_aes_128(key, buf, len, mic);
#endif /* CONFIG_SAE */
#ifdef CONFIG_HS20
		case WPA_KEY_MGMT_OSEN:
			wpa_printf(MSG_DEBUG,
				   "WPA: EAPOL-Key MIC using AES-CMAC (AKM-defined - OSEN)");
			return omac1_aes_128(key, buf, len, mic);
#endif /* CONFIG_HS20 */
#ifdef CONFIG_SUITEB
		case WPA_KEY_MGMT_IEEE8021X_SUITE_B:
			wpa_printf(MSG_DEBUG,
				   "WPA: EAPOL-Key MIC using HMAC-SHA256 (AKM-defined - Suite B)");
			if (hmac_sha256(key, key_len, buf, len, hash))
				return -1;
			os_memcpy(mic, hash, MD5_MAC_LEN);
			break;
#endif /* CONFIG_SUITEB */
#ifdef CONFIG_SUITEB192
		case WPA_KEY_MGMT_IEEE8021X_SUITE_B_192:
			wpa_printf(MSG_DEBUG,
				   "WPA: EAPOL-Key MIC using HMAC-SHA384 (AKM-defined - Suite B 192-bit)");
			if (hmac_sha384(key, key_len, buf, len, hash))
				return -1;
			os_memcpy(mic, hash, 24);
			break;
#endif /* CONFIG_SUITEB192 */
#ifdef CONFIG_OWE
		case WPA_KEY_MGMT_OWE:
			wpa_printf(MSG_DEBUG,
				   "WPA: EAPOL-Key MIC using HMAC-SHA%u (AKM-defined - OWE)",
				   (unsigned int) key_len * 8 * 2);
			if (key_len == 128 / 8) {
				if (hmac_sha256(key, key_len, buf, len, hash))
					return -1;
			} else if (key_len == 192 / 8) {
				if (hmac_sha384(key, key_len, buf, len, hash))
					return -1;
			} else if (key_len == 256 / 8) {
				if (hmac_sha512(key, key_len, buf, len, hash))
					return -1;
			} else {
				wpa_printf(MSG_INFO,
					   "OWE: Unsupported KCK length: %u",
					   (unsigned int) key_len);
				return -1;
			}
			os_memcpy(mic, hash, key_len);
			break;
#endif /* CONFIG_OWE */
#ifdef CONFIG_DPP
		case WPA_KEY_MGMT_DPP:
			wpa_printf(MSG_DEBUG,
				   "WPA: EAPOL-Key MIC using HMAC-SHA%u (AKM-defined - DPP)",
				   (unsigned int) key_len * 8 * 2);
			if (key_len == 128 / 8) {
				if (hmac_sha256(key, key_len, buf, len, hash))
					return -1;
			} else if (key_len == 192 / 8) {
				if (hmac_sha384(key, key_len, buf, len, hash))
					return -1;
			} else if (key_len == 256 / 8) {
				if (hmac_sha512(key, key_len, buf, len, hash))
					return -1;
			} else {
				wpa_printf(MSG_INFO,
					   "DPP: Unsupported KCK length: %u",
					   (unsigned int) key_len);
				return -1;
			}
			os_memcpy(mic, hash, key_len);
			break;
#endif /* CONFIG_DPP */
#if defined(CONFIG_IEEE80211R) && defined(CONFIG_SHA384)
		case WPA_KEY_MGMT_FT_IEEE8021X_SHA384:
			wpa_printf(MSG_DEBUG,
				   "WPA: EAPOL-Key MIC using HMAC-SHA384 (AKM-defined - FT 802.1X SHA384)");
			if (hmac_sha384(key, key_len, buf, len, hash))
				return -1;
			os_memcpy(mic, hash, 24);
			break;
#endif /* CONFIG_IEEE80211R && CONFIG_SHA384 */
		default:
			wpa_printf(MSG_DEBUG,
				   "WPA: EAPOL-Key MIC algorithm not known (AKM-defined - akmp=0x%x)",
				   akmp);
			return -1;
		}
		break;
	default:
		wpa_printf(MSG_DEBUG,
			   "WPA: EAPOL-Key MIC algorithm not known (ver=%d)",
			   ver);
		return -1;
	}

	return 0;
}