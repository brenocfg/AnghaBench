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
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  PMKID_LEN ; 
 int SHA384_MAC_LEN ; 
 int /*<<< orphan*/  hmac_sha1_vector (int /*<<< orphan*/  const*,size_t,int,int /*<<< orphan*/  const**,size_t const*,unsigned char*) ; 
 int /*<<< orphan*/  hmac_sha256_vector (int /*<<< orphan*/  const*,size_t,int,int /*<<< orphan*/  const**,size_t const*,unsigned char*) ; 
 int /*<<< orphan*/  hmac_sha384_vector (int /*<<< orphan*/  const*,size_t,int,int /*<<< orphan*/  const**,size_t const*,unsigned char*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,unsigned char*,int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_key_mgmt_sha256 (int) ; 
 scalar_t__ wpa_key_mgmt_sha384 (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

void rsn_pmkid(const u8 *pmk, size_t pmk_len, const u8 *aa, const u8 *spa,
	       u8 *pmkid, int akmp)
{
	char *title = "PMK Name";
	const u8 *addr[3];
	const size_t len[3] = { 8, ETH_ALEN, ETH_ALEN };
	unsigned char hash[SHA384_MAC_LEN];

	addr[0] = (u8 *) title;
	addr[1] = aa;
	addr[2] = spa;

	if (0) {
#if defined(CONFIG_FILS) || defined(CONFIG_SHA384)
	} else if (wpa_key_mgmt_sha384(akmp)) {
		wpa_printf(MSG_DEBUG, "RSN: Derive PMKID using HMAC-SHA-384");
		hmac_sha384_vector(pmk, pmk_len, 3, addr, len, hash);
#endif /* CONFIG_FILS || CONFIG_SHA384 */
#if defined(CONFIG_IEEE80211W) || defined(CONFIG_FILS)
	} else if (wpa_key_mgmt_sha256(akmp)) {
		wpa_printf(MSG_DEBUG, "RSN: Derive PMKID using HMAC-SHA-256");
		hmac_sha256_vector(pmk, pmk_len, 3, addr, len, hash);
#endif /* CONFIG_IEEE80211W || CONFIG_FILS */
	} else {
		wpa_printf(MSG_DEBUG, "RSN: Derive PMKID using HMAC-SHA-1");
		hmac_sha1_vector(pmk, pmk_len, 3, addr, len, hash);
	}
	wpa_hexdump(MSG_DEBUG, "RSN: Derived PMKID", hash, PMKID_LEN);
	os_memcpy(pmkid, hash, PMKID_LEN);
}