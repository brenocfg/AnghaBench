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
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int SHA256_MAC_LEN ; 
 struct wpabuf* dpp_get_pubkey_point (int /*<<< orphan*/ *,int) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int sha256_vector (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  const* wpabuf_head (struct wpabuf*) ; 
 int wpabuf_len (struct wpabuf*) ; 

__attribute__((used)) static int dpp_check_pubkey_match(EVP_PKEY *pub, struct wpabuf *r_hash)
{
	struct wpabuf *uncomp;
	int res;
	u8 hash[SHA256_MAC_LEN];
	const u8 *addr[1];
	size_t len[1];

	if (wpabuf_len(r_hash) != SHA256_MAC_LEN)
		return -1;
	uncomp = dpp_get_pubkey_point(pub, 1);
	if (!uncomp)
		return -1;
	addr[0] = wpabuf_head(uncomp);
	len[0] = wpabuf_len(uncomp);
	wpa_hexdump(MSG_DEBUG, "DPP: Uncompressed public key",
		    addr[0], len[0]);
	res = sha256_vector(1, addr, len, hash);
	wpabuf_free(uncomp);
	if (res < 0)
		return -1;
	if (os_memcmp(hash, wpabuf_head(r_hash), SHA256_MAC_LEN) != 0) {
		wpa_printf(MSG_DEBUG,
			   "DPP: Received hash value does not match calculated public key hash value");
		wpa_hexdump(MSG_DEBUG, "DPP: Calculated hash",
			    hash, SHA256_MAC_LEN);
		return -1;
	}
	return 0;
}