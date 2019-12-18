#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  encr; int /*<<< orphan*/  prf; int /*<<< orphan*/  integ; } ;
struct ikev2_responder_data {int i_nonce_len; int r_nonce_len; int /*<<< orphan*/  keys; struct wpabuf* r_dh_private; struct wpabuf* i_dh_public; TYPE_2__* dh; int /*<<< orphan*/  r_spi; int /*<<< orphan*/  i_spi; int /*<<< orphan*/  r_nonce; int /*<<< orphan*/  i_nonce; TYPE_1__ proposal; } ;
struct ikev2_prf_alg {int /*<<< orphan*/  hash_len; int /*<<< orphan*/  id; } ;
struct ikev2_integ_alg {int dummy; } ;
struct ikev2_encr_alg {int dummy; } ;
struct TYPE_4__ {size_t prime_len; } ;

/* Variables and functions */
 int IKEV2_MAX_HASH_LEN ; 
 int IKEV2_SPI_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 struct wpabuf* dh_derive_shared (struct wpabuf*,struct wpabuf*,TYPE_2__*) ; 
 int ikev2_derive_sk_keys (struct ikev2_prf_alg const*,struct ikev2_integ_alg const*,struct ikev2_encr_alg const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 struct ikev2_encr_alg* ikev2_get_encr (int /*<<< orphan*/ ) ; 
 struct ikev2_integ_alg* ikev2_get_integ (int /*<<< orphan*/ ) ; 
 struct ikev2_prf_alg* ikev2_get_prf (int /*<<< orphan*/ ) ; 
 scalar_t__ ikev2_prf_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * os_zalloc (size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/ * wpabuf_head (struct wpabuf*) ; 
 size_t wpabuf_len (struct wpabuf*) ; 

__attribute__((used)) static int ikev2_derive_keys(struct ikev2_responder_data *data)
{
	u8 *buf, *pos, *pad, skeyseed[IKEV2_MAX_HASH_LEN];
	size_t buf_len, pad_len;
	struct wpabuf *shared;
	const struct ikev2_integ_alg *integ;
	const struct ikev2_prf_alg *prf;
	const struct ikev2_encr_alg *encr;
	int ret;
	const u8 *addr[2];
	size_t len[2];

	/* RFC 4306, Sect. 2.14 */

	integ = ikev2_get_integ(data->proposal.integ);
	prf = ikev2_get_prf(data->proposal.prf);
	encr = ikev2_get_encr(data->proposal.encr);
	if (integ == NULL || prf == NULL || encr == NULL) {
		wpa_printf(MSG_INFO, "IKEV2: Unsupported proposal");
		return -1;
	}

	shared = dh_derive_shared(data->i_dh_public, data->r_dh_private,
				  data->dh);
	if (shared == NULL)
		return -1;

	/* Construct Ni | Nr | SPIi | SPIr */

	buf_len = data->i_nonce_len + data->r_nonce_len + 2 * IKEV2_SPI_LEN;
	buf = os_malloc(buf_len);
	if (buf == NULL) {
		wpabuf_free(shared);
		return -1;
	}

	pos = buf;
	os_memcpy(pos, data->i_nonce, data->i_nonce_len);
	pos += data->i_nonce_len;
	os_memcpy(pos, data->r_nonce, data->r_nonce_len);
	pos += data->r_nonce_len;
	os_memcpy(pos, data->i_spi, IKEV2_SPI_LEN);
	pos += IKEV2_SPI_LEN;
	os_memcpy(pos, data->r_spi, IKEV2_SPI_LEN);

	/* SKEYSEED = prf(Ni | Nr, g^ir) */
	/* Use zero-padding per RFC 4306, Sect. 2.14 */
	pad_len = data->dh->prime_len - wpabuf_len(shared);
	pad = os_zalloc(pad_len ? pad_len : 1);
	if (pad == NULL) {
		wpabuf_free(shared);
		os_free(buf);
		return -1;
	}

	addr[0] = pad;
	len[0] = pad_len;
	addr[1] = wpabuf_head(shared);
	len[1] = wpabuf_len(shared);
	if (ikev2_prf_hash(prf->id, buf, data->i_nonce_len + data->r_nonce_len,
			   2, addr, len, skeyseed) < 0) {
		wpabuf_free(shared);
		os_free(buf);
		os_free(pad);
		return -1;
	}
	os_free(pad);
	wpabuf_free(shared);

	/* DH parameters are not needed anymore, so free them */
	wpabuf_free(data->i_dh_public);
	data->i_dh_public = NULL;
	wpabuf_free(data->r_dh_private);
	data->r_dh_private = NULL;

	wpa_hexdump_key(MSG_DEBUG, "IKEV2: SKEYSEED",
			skeyseed, prf->hash_len);

	ret = ikev2_derive_sk_keys(prf, integ, encr, skeyseed, buf, buf_len,
				   &data->keys);
	os_free(buf);
	return ret;
}