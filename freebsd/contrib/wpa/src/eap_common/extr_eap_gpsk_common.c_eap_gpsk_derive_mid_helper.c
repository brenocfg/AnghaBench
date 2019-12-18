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
typedef  int /*<<< orphan*/  const u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
#define  EAP_GPSK_CIPHER_AES 129 
#define  EAP_GPSK_CIPHER_SHA256 128 
 int /*<<< orphan*/  EAP_GPSK_VENDOR_IETF ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  const* SID_LABEL ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPA_PUT_BE32 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int eap_gpsk_gkdf_cmac (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t) ; 
 int eap_gpsk_gkdf_sha256 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 size_t strlen (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eap_gpsk_derive_mid_helper(u32 csuite_specifier,
				      u8 *kdf_out, size_t kdf_out_len,
				      const u8 *psk, const u8 *seed,
				      size_t seed_len, u8 method_type)
{
	u8 *pos, *data;
	size_t data_len;
	int (*gkdf)(const u8 *_psk, const u8 *_data, size_t _data_len,
		    u8 *buf, size_t len);

	gkdf = NULL;
	switch (csuite_specifier) {
	case EAP_GPSK_CIPHER_AES:
		gkdf = eap_gpsk_gkdf_cmac;
		break;
#ifdef EAP_GPSK_SHA256
	case EAP_GPSK_CIPHER_SHA256:
		gkdf = eap_gpsk_gkdf_sha256;
		break;
#endif /* EAP_GPSK_SHA256 */
	default:
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Unknown cipher %d used in "
			   "Session-Id derivation", csuite_specifier);
		return -1;
	}

#define SID_LABEL "Method ID"
	/* "Method ID" || EAP_Method_Type || CSuite_Sel || inputString */
	data_len = strlen(SID_LABEL) + 1 + 6 + seed_len;
	data = os_malloc(data_len);
	if (data == NULL)
		return -1;
	pos = data;
	os_memcpy(pos, SID_LABEL, strlen(SID_LABEL));
	pos += strlen(SID_LABEL);
#undef SID_LABEL
	os_memcpy(pos, &method_type, 1);
	pos += 1;
	WPA_PUT_BE32(pos, EAP_GPSK_VENDOR_IETF); /* CSuite/Vendor = IETF */
	pos += 4;
	WPA_PUT_BE16(pos, csuite_specifier); /* CSuite/Specifier */
	pos += 2;
	os_memcpy(pos, seed, seed_len); /* inputString */
	wpa_hexdump(MSG_DEBUG, "EAP-GPSK: Data to Method ID derivation",
		    data, data_len);

	if (gkdf(psk, data, data_len, kdf_out, kdf_out_len) < 0) {
		os_free(data);
		return -1;
	}
	os_free(data);
	wpa_hexdump(MSG_DEBUG, "EAP-GPSK: Method ID", kdf_out, kdf_out_len);

	return 0;
}