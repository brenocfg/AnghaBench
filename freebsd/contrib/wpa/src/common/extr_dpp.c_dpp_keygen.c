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
struct dpp_bootstrap_info {int own; int /*<<< orphan*/  pubkey_hash; int /*<<< orphan*/  pubkey; int /*<<< orphan*/ * curve; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  SHA256_MAC_LEN ; 
 unsigned char* base64_encode (int /*<<< orphan*/ *,size_t,size_t*) ; 
 struct wpabuf* dpp_bootstrap_key_der (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dpp_curves ; 
 int /*<<< orphan*/  dpp_gen_keypair (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dpp_get_curve_name (char const*) ; 
 int /*<<< orphan*/  dpp_set_keypair (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  os_free (unsigned char*) ; 
 int /*<<< orphan*/  os_memmove (char*,char*,int) ; 
 char* os_strchr (char*,char) ; 
 int sha256_vector (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/ * wpabuf_head (struct wpabuf*) ; 
 size_t wpabuf_len (struct wpabuf*) ; 

char * dpp_keygen(struct dpp_bootstrap_info *bi, const char *curve,
		  const u8 *privkey, size_t privkey_len)
{
	unsigned char *base64 = NULL;
	char *pos, *end;
	size_t len;
	struct wpabuf *der = NULL;
	const u8 *addr[1];
	int res;

	if (!curve) {
		bi->curve = &dpp_curves[0];
	} else {
		bi->curve = dpp_get_curve_name(curve);
		if (!bi->curve) {
			wpa_printf(MSG_INFO, "DPP: Unsupported curve: %s",
				   curve);
			return NULL;
		}
	}
	if (privkey)
		bi->pubkey = dpp_set_keypair(&bi->curve, privkey, privkey_len);
	else
		bi->pubkey = dpp_gen_keypair(bi->curve);
	if (!bi->pubkey)
		goto fail;
	bi->own = 1;

	der = dpp_bootstrap_key_der(bi->pubkey);
	if (!der)
		goto fail;
	wpa_hexdump_buf(MSG_DEBUG, "DPP: Compressed public key (DER)",
			der);

	addr[0] = wpabuf_head(der);
	len = wpabuf_len(der);
	res = sha256_vector(1, addr, &len, bi->pubkey_hash);
	if (res < 0) {
		wpa_printf(MSG_DEBUG, "DPP: Failed to hash public key");
		goto fail;
	}
	wpa_hexdump(MSG_DEBUG, "DPP: Public key hash", bi->pubkey_hash,
		    SHA256_MAC_LEN);

	base64 = base64_encode(wpabuf_head(der), wpabuf_len(der), &len);
	wpabuf_free(der);
	der = NULL;
	if (!base64)
		goto fail;
	pos = (char *) base64;
	end = pos + len;
	for (;;) {
		pos = os_strchr(pos, '\n');
		if (!pos)
			break;
		os_memmove(pos, pos + 1, end - pos);
	}
	return (char *) base64;
fail:
	os_free(base64);
	wpabuf_free(der);
	return NULL;
}