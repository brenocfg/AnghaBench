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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  tmp ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int hmac_sha1 (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int hmac_sha256 (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int hmac_sha384 (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ tls_cipher_suite_mac_sha1 (int /*<<< orphan*/ ) ; 
 scalar_t__ tls_cipher_suite_mac_sha256 (int /*<<< orphan*/ ) ; 
 scalar_t__ tls_cipher_suite_mac_sha384 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int eap_teap_tls_mac(u16 tls_cs, const u8 *cmk, size_t cmk_len,
			    const u8 *buffer, size_t buffer_len,
			    u8 *mac, size_t mac_len)
{
	int res;
	u8 tmp[48];

	os_memset(tmp, 0, sizeof(tmp));
	os_memset(mac, 0, mac_len);

	if (tls_cipher_suite_mac_sha1(tls_cs)) {
		wpa_printf(MSG_DEBUG, "EAP-TEAP: MAC algorithm: HMAC-SHA1");
		res = hmac_sha1(cmk, cmk_len, buffer, buffer_len, tmp);
	} else if (tls_cipher_suite_mac_sha256(tls_cs)) {
		wpa_printf(MSG_DEBUG, "EAP-TEAP: MAC algorithm: HMAC-SHA256");
		res = hmac_sha256(cmk, cmk_len, buffer, buffer_len, tmp);
	} else if (tls_cipher_suite_mac_sha384(tls_cs)) {
		wpa_printf(MSG_DEBUG, "EAP-TEAP: MAC algorithm: HMAC-SHA384");
		res = hmac_sha384(cmk, cmk_len, buffer, buffer_len, tmp);
	} else {
		wpa_printf(MSG_INFO,
			   "EAP-TEAP: Unsupported TLS cipher suite 0x%04x",
			   tls_cs);
		res = -1;
	}
	if (res < 0)
		return res;

	/* FIX: RFC 7170 does not describe how to handle truncation of the
	 * Compound MAC or if the fields are supposed to be of variable length
	 * based on the negotiated TLS cipher suite (they are defined as having
	 * fixed size of 20 octets in the TLV description) */
	if (mac_len > sizeof(tmp))
		mac_len = sizeof(tmp);
	os_memcpy(mac, tmp, mac_len);
	return 0;
}