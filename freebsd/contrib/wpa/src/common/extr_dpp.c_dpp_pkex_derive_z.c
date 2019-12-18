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
typedef  char u8 ;

/* Variables and functions */
 int DPP_MAX_HASH_LEN ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ dpp_hmac (unsigned int,char*,unsigned int,char const*,size_t,char*) ; 
 int hmac_sha256_kdf (char*,unsigned int,int /*<<< orphan*/ *,char*,size_t,char*,unsigned int) ; 
 int hmac_sha384_kdf (char*,unsigned int,int /*<<< orphan*/ *,char*,size_t,char*,unsigned int) ; 
 int hmac_sha512_kdf (char*,unsigned int,int /*<<< orphan*/ *,char*,size_t,char*,unsigned int) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  os_memset (char*,int /*<<< orphan*/ ,unsigned int) ; 
 size_t os_strlen (char const*) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,char*,unsigned int) ; 

__attribute__((used)) static int dpp_pkex_derive_z(const u8 *mac_init, const u8 *mac_resp,
			     const u8 *Mx, size_t Mx_len,
			     const u8 *Nx, size_t Nx_len,
			     const char *code,
			     const u8 *Kx, size_t Kx_len,
			     u8 *z, unsigned int hash_len)
{
	u8 salt[DPP_MAX_HASH_LEN], prk[DPP_MAX_HASH_LEN];
	int res;
	u8 *info, *pos;
	size_t info_len;

	/* z = HKDF(<>, MAC-Initiator | MAC-Responder | M.x | N.x | code, K.x)
	 */

	/* HKDF-Extract(<>, IKM=K.x) */
	os_memset(salt, 0, hash_len);
	if (dpp_hmac(hash_len, salt, hash_len, Kx, Kx_len, prk) < 0)
		return -1;
	wpa_hexdump_key(MSG_DEBUG, "DPP: PRK = HKDF-Extract(<>, IKM)",
			prk, hash_len);
	info_len = 2 * ETH_ALEN + Mx_len + Nx_len + os_strlen(code);
	info = os_malloc(info_len);
	if (!info)
		return -1;
	pos = info;
	os_memcpy(pos, mac_init, ETH_ALEN);
	pos += ETH_ALEN;
	os_memcpy(pos, mac_resp, ETH_ALEN);
	pos += ETH_ALEN;
	os_memcpy(pos, Mx, Mx_len);
	pos += Mx_len;
	os_memcpy(pos, Nx, Nx_len);
	pos += Nx_len;
	os_memcpy(pos, code, os_strlen(code));

	/* HKDF-Expand(PRK, info, L) */
	if (hash_len == 32)
		res = hmac_sha256_kdf(prk, hash_len, NULL, info, info_len,
				      z, hash_len);
	else if (hash_len == 48)
		res = hmac_sha384_kdf(prk, hash_len, NULL, info, info_len,
				      z, hash_len);
	else if (hash_len == 64)
		res = hmac_sha512_kdf(prk, hash_len, NULL, info, info_len,
				      z, hash_len);
	else
		res = -1;
	os_free(info);
	os_memset(prk, 0, hash_len);
	if (res < 0)
		return -1;

	wpa_hexdump_key(MSG_DEBUG, "DPP: z = HKDF-Expand(PRK, info, L)",
			z, hash_len);
	return 0;
}