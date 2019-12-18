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
struct wpabuf {int dummy; } ;
struct dpp_curve_params {int dummy; } ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int PMKID_LEN ; 
 int SHA256_MAC_LEN ; 
 struct wpabuf* dpp_get_pubkey_point (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int sha256_vector (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  const* wpabuf_head (struct wpabuf*) ; 
 int wpabuf_len (struct wpabuf*) ; 

__attribute__((used)) static int dpp_derive_pmkid(const struct dpp_curve_params *curve,
			    EVP_PKEY *own_key, EVP_PKEY *peer_key, u8 *pmkid)
{
	struct wpabuf *nkx, *pkx;
	int ret = -1, res;
	const u8 *addr[2];
	size_t len[2];
	u8 hash[SHA256_MAC_LEN];

	/* PMKID = Truncate-128(H(min(NK.x, PK.x) | max(NK.x, PK.x))) */
	nkx = dpp_get_pubkey_point(own_key, 0);
	pkx = dpp_get_pubkey_point(peer_key, 0);
	if (!nkx || !pkx)
		goto fail;
	addr[0] = wpabuf_head(nkx);
	len[0] = wpabuf_len(nkx) / 2;
	addr[1] = wpabuf_head(pkx);
	len[1] = wpabuf_len(pkx) / 2;
	if (len[0] != len[1])
		goto fail;
	if (os_memcmp(addr[0], addr[1], len[0]) > 0) {
		addr[0] = wpabuf_head(pkx);
		addr[1] = wpabuf_head(nkx);
	}
	wpa_hexdump(MSG_DEBUG, "DPP: PMKID hash payload 1", addr[0], len[0]);
	wpa_hexdump(MSG_DEBUG, "DPP: PMKID hash payload 2", addr[1], len[1]);
	res = sha256_vector(2, addr, len, hash);
	if (res < 0)
		goto fail;
	wpa_hexdump(MSG_DEBUG, "DPP: PMKID hash output", hash, SHA256_MAC_LEN);
	os_memcpy(pmkid, hash, PMKID_LEN);
	wpa_hexdump(MSG_DEBUG, "DPP: PMKID", pmkid, PMKID_LEN);
	ret = 0;
fail:
	wpabuf_free(nkx);
	wpabuf_free(pkx);
	return ret;
}