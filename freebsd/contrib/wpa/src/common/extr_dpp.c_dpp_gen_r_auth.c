#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const u8 ;
struct wpabuf {int dummy; } ;
struct dpp_authentication {TYPE_3__* curve; int /*<<< orphan*/  const* r_nonce; int /*<<< orphan*/  const* i_nonce; TYPE_2__* own_bi; TYPE_1__* peer_bi; int /*<<< orphan*/  own_protocol_key; int /*<<< orphan*/  peer_protocol_key; scalar_t__ initiator; } ;
struct TYPE_6__ {size_t nonce_len; size_t hash_len; } ;
struct TYPE_5__ {int /*<<< orphan*/  pubkey; } ;
struct TYPE_4__ {int /*<<< orphan*/  pubkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 struct wpabuf* dpp_get_pubkey_point (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dpp_hash_vector (TYPE_3__*,size_t,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  const* wpabuf_head (struct wpabuf*) ; 
 int wpabuf_len (struct wpabuf*) ; 

__attribute__((used)) static int dpp_gen_r_auth(struct dpp_authentication *auth, u8 *r_auth)
{
	struct wpabuf *pix, *prx, *bix, *brx;
	const u8 *addr[7];
	size_t len[7];
	size_t i, num_elem = 0;
	size_t nonce_len;
	u8 zero = 0;
	int res = -1;

	/* R-auth = H(I-nonce | R-nonce | PI.x | PR.x | [BI.x |] BR.x | 0) */
	nonce_len = auth->curve->nonce_len;

	if (auth->initiator) {
		pix = dpp_get_pubkey_point(auth->own_protocol_key, 0);
		prx = dpp_get_pubkey_point(auth->peer_protocol_key, 0);
		if (auth->own_bi)
			bix = dpp_get_pubkey_point(auth->own_bi->pubkey, 0);
		else
			bix = NULL;
		brx = dpp_get_pubkey_point(auth->peer_bi->pubkey, 0);
	} else {
		pix = dpp_get_pubkey_point(auth->peer_protocol_key, 0);
		prx = dpp_get_pubkey_point(auth->own_protocol_key, 0);
		if (auth->peer_bi)
			bix = dpp_get_pubkey_point(auth->peer_bi->pubkey, 0);
		else
			bix = NULL;
		brx = dpp_get_pubkey_point(auth->own_bi->pubkey, 0);
	}
	if (!pix || !prx || !brx)
		goto fail;

	addr[num_elem] = auth->i_nonce;
	len[num_elem] = nonce_len;
	num_elem++;

	addr[num_elem] = auth->r_nonce;
	len[num_elem] = nonce_len;
	num_elem++;

	addr[num_elem] = wpabuf_head(pix);
	len[num_elem] = wpabuf_len(pix) / 2;
	num_elem++;

	addr[num_elem] = wpabuf_head(prx);
	len[num_elem] = wpabuf_len(prx) / 2;
	num_elem++;

	if (bix) {
		addr[num_elem] = wpabuf_head(bix);
		len[num_elem] = wpabuf_len(bix) / 2;
		num_elem++;
	}

	addr[num_elem] = wpabuf_head(brx);
	len[num_elem] = wpabuf_len(brx) / 2;
	num_elem++;

	addr[num_elem] = &zero;
	len[num_elem] = 1;
	num_elem++;

	wpa_printf(MSG_DEBUG, "DPP: R-auth hash components");
	for (i = 0; i < num_elem; i++)
		wpa_hexdump(MSG_DEBUG, "DPP: hash component", addr[i], len[i]);
	res = dpp_hash_vector(auth->curve, num_elem, addr, len, r_auth);
	if (res == 0)
		wpa_hexdump(MSG_DEBUG, "DPP: R-auth", r_auth,
			    auth->curve->hash_len);
fail:
	wpabuf_free(pix);
	wpabuf_free(prx);
	wpabuf_free(bix);
	wpabuf_free(brx);
	return res;
}