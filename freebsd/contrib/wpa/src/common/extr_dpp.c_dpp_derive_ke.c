#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct dpp_authentication {size_t Mx_len; size_t Nx_len; size_t secret_len; int /*<<< orphan*/ * Lx; int /*<<< orphan*/  Lx_len; scalar_t__ own_bi; scalar_t__ peer_bi; int /*<<< orphan*/ * Nx; int /*<<< orphan*/ * Mx; int /*<<< orphan*/  r_nonce; int /*<<< orphan*/  i_nonce; TYPE_1__* curve; } ;
struct TYPE_2__ {size_t nonce_len; } ;

/* Variables and functions */
 int DPP_MAX_HASH_LEN ; 
 int DPP_MAX_NONCE_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int dpp_hkdf_expand (unsigned int,int /*<<< orphan*/ *,unsigned int,char const*,int /*<<< orphan*/ *,unsigned int) ; 
 int dpp_hmac_vector (unsigned int,int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int dpp_derive_ke(struct dpp_authentication *auth, u8 *ke,
			 unsigned int hash_len)
{
	size_t nonce_len;
	u8 nonces[2 * DPP_MAX_NONCE_LEN];
	const char *info_ke = "DPP Key";
	u8 prk[DPP_MAX_HASH_LEN];
	int res;
	const u8 *addr[3];
	size_t len[3];
	size_t num_elem = 0;

	if (!auth->Mx_len || !auth->Nx_len) {
		wpa_printf(MSG_DEBUG,
			   "DPP: Mx/Nx not available - cannot derive ke");
		return -1;
	}

	/* ke = HKDF(I-nonce | R-nonce, "DPP Key", M.x | N.x [| L.x]) */

	/* HKDF-Extract(I-nonce | R-nonce, M.x | N.x [| L.x]) */
	nonce_len = auth->curve->nonce_len;
	os_memcpy(nonces, auth->i_nonce, nonce_len);
	os_memcpy(&nonces[nonce_len], auth->r_nonce, nonce_len);
	addr[num_elem] = auth->Mx;
	len[num_elem] = auth->Mx_len;
	num_elem++;
	addr[num_elem] = auth->Nx;
	len[num_elem] = auth->Nx_len;
	num_elem++;
	if (auth->peer_bi && auth->own_bi) {
		if (!auth->Lx_len) {
			wpa_printf(MSG_DEBUG,
				   "DPP: Lx not available - cannot derive ke");
			return -1;
		}
		addr[num_elem] = auth->Lx;
		len[num_elem] = auth->secret_len;
		num_elem++;
	}
	res = dpp_hmac_vector(hash_len, nonces, 2 * nonce_len,
			      num_elem, addr, len, prk);
	if (res < 0)
		return -1;
	wpa_hexdump_key(MSG_DEBUG, "DPP: PRK = HKDF-Extract(<>, IKM)",
			prk, hash_len);

	/* HKDF-Expand(PRK, info, L) */
	res = dpp_hkdf_expand(hash_len, prk, hash_len, info_ke, ke, hash_len);
	os_memset(prk, 0, hash_len);
	if (res < 0)
		return -1;

	wpa_hexdump_key(MSG_DEBUG, "DPP: ke = HKDF-Expand(PRK, info, L)",
			ke, hash_len);
	return 0;
}