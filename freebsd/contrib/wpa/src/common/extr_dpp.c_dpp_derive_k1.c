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
 int DPP_MAX_HASH_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int dpp_hkdf_expand (unsigned int,int /*<<< orphan*/ *,unsigned int,char const*,int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ dpp_hmac (unsigned int,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int dpp_derive_k1(const u8 *Mx, size_t Mx_len, u8 *k1,
			 unsigned int hash_len)
{
	u8 salt[DPP_MAX_HASH_LEN], prk[DPP_MAX_HASH_LEN];
	const char *info = "first intermediate key";
	int res;

	/* k1 = HKDF(<>, "first intermediate key", M.x) */

	/* HKDF-Extract(<>, M.x) */
	os_memset(salt, 0, hash_len);
	if (dpp_hmac(hash_len, salt, hash_len, Mx, Mx_len, prk) < 0)
		return -1;
	wpa_hexdump_key(MSG_DEBUG, "DPP: PRK = HKDF-Extract(<>, IKM=M.x)",
			prk, hash_len);

	/* HKDF-Expand(PRK, info, L) */
	res = dpp_hkdf_expand(hash_len, prk, hash_len, info, k1, hash_len);
	os_memset(prk, 0, hash_len);
	if (res < 0)
		return -1;

	wpa_hexdump_key(MSG_DEBUG, "DPP: k1 = HKDF-Expand(PRK, info, L)",
			k1, hash_len);
	return 0;
}