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
struct dpp_curve_params {char* jwk_crv; int /*<<< orphan*/  prime_len; } ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 scalar_t__ base64_url_encode (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct wpabuf* dpp_get_pubkey_point (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/ * wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_str (struct wpabuf*,char const*) ; 

__attribute__((used)) static int dpp_build_jwk(struct wpabuf *buf, const char *name, EVP_PKEY *key,
			 const char *kid, const struct dpp_curve_params *curve)
{
	struct wpabuf *pub;
	const u8 *pos;
	char *x = NULL, *y = NULL;
	int ret = -1;

	pub = dpp_get_pubkey_point(key, 0);
	if (!pub)
		goto fail;
	pos = wpabuf_head(pub);
	x = (char *) base64_url_encode(pos, curve->prime_len, NULL, 0);
	pos += curve->prime_len;
	y = (char *) base64_url_encode(pos, curve->prime_len, NULL, 0);
	if (!x || !y)
		goto fail;

	wpabuf_put_str(buf, "\"");
	wpabuf_put_str(buf, name);
	wpabuf_put_str(buf, "\":{\"kty\":\"EC\",\"crv\":\"");
	wpabuf_put_str(buf, curve->jwk_crv);
	wpabuf_put_str(buf, "\",\"x\":\"");
	wpabuf_put_str(buf, x);
	wpabuf_put_str(buf, "\",\"y\":\"");
	wpabuf_put_str(buf, y);
	if (kid) {
		wpabuf_put_str(buf, "\",\"kid\":\"");
		wpabuf_put_str(buf, kid);
	}
	wpabuf_put_str(buf, "\"}");
	ret = 0;
fail:
	wpabuf_free(pub);
	os_free(x);
	os_free(y);
	return ret;
}