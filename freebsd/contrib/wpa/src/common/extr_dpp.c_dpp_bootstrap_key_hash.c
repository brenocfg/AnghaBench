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
struct wpabuf {int dummy; } ;
struct dpp_bootstrap_info {int /*<<< orphan*/  pubkey_hash; int /*<<< orphan*/  pubkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  SHA256_MAC_LEN ; 
 struct wpabuf* dpp_bootstrap_key_der (int /*<<< orphan*/ ) ; 
 int sha256_vector (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/ * wpabuf_head (struct wpabuf*) ; 
 size_t wpabuf_len (struct wpabuf*) ; 

int dpp_bootstrap_key_hash(struct dpp_bootstrap_info *bi)
{
	struct wpabuf *der;
	int res;
	const u8 *addr[1];
	size_t len[1];

	der = dpp_bootstrap_key_der(bi->pubkey);
	if (!der)
		return -1;
	wpa_hexdump_buf(MSG_DEBUG, "DPP: Compressed public key (DER)",
			der);

	addr[0] = wpabuf_head(der);
	len[0] = wpabuf_len(der);
	res = sha256_vector(1, addr, len, bi->pubkey_hash);
	if (res < 0)
		wpa_printf(MSG_DEBUG, "DPP: Failed to hash public key");
	else
		wpa_hexdump(MSG_DEBUG, "DPP: Public key hash", bi->pubkey_hash,
			    SHA256_MAC_LEN);
	wpabuf_free(der);
	return res;
}