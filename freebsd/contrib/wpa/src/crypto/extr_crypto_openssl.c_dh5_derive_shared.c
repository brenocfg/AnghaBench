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
struct wpabuf {int dummy; } ;
typedef  int /*<<< orphan*/  DH ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int DH_compute_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t DH_size (int /*<<< orphan*/ *) ; 
 struct wpabuf* wpabuf_alloc (size_t) ; 
 int /*<<< orphan*/  wpabuf_clear_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_mhead (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put (struct wpabuf*,int) ; 

struct wpabuf * dh5_derive_shared(void *ctx, const struct wpabuf *peer_public,
				  const struct wpabuf *own_private)
{
	BIGNUM *pub_key;
	struct wpabuf *res = NULL;
	size_t rlen;
	DH *dh = ctx;
	int keylen;

	if (ctx == NULL)
		return NULL;

	pub_key = BN_bin2bn(wpabuf_head(peer_public), wpabuf_len(peer_public),
			    NULL);
	if (pub_key == NULL)
		return NULL;

	rlen = DH_size(dh);
	res = wpabuf_alloc(rlen);
	if (res == NULL)
		goto err;

	keylen = DH_compute_key(wpabuf_mhead(res), pub_key, dh);
	if (keylen < 0)
		goto err;
	wpabuf_put(res, keylen);
	BN_clear_free(pub_key);

	return res;

err:
	BN_clear_free(pub_key);
	wpabuf_clear_free(res);
	return NULL;
}