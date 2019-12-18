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
struct dh_group {size_t prime_len; int /*<<< orphan*/  prime; int /*<<< orphan*/ * generator; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ crypto_dh_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_hexdump_buf_key (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (size_t) ; 
 int /*<<< orphan*/  wpabuf_clear_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_mhead (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put (struct wpabuf*,size_t) ; 

struct wpabuf * dh_init(const struct dh_group *dh, struct wpabuf **priv)
{
	struct wpabuf *pv;
	size_t pv_len;

	if (dh == NULL)
		return NULL;

	wpabuf_clear_free(*priv);
	*priv = wpabuf_alloc(dh->prime_len);
	if (*priv == NULL)
		return NULL;

	pv_len = dh->prime_len;
	pv = wpabuf_alloc(pv_len);
	if (pv == NULL) {
		wpabuf_clear_free(*priv);
		*priv = NULL;
		return NULL;
	}
	if (crypto_dh_init(*dh->generator, dh->prime, dh->prime_len,
			   wpabuf_mhead(*priv), wpabuf_mhead(pv)) < 0) {
		wpabuf_clear_free(pv);
		wpa_printf(MSG_INFO, "DH: crypto_dh_init failed");
		wpabuf_clear_free(*priv);
		*priv = NULL;
		return NULL;
	}
	wpabuf_put(*priv, dh->prime_len);
	wpabuf_put(pv, dh->prime_len);
	wpa_hexdump_buf_key(MSG_DEBUG, "DH: private value", *priv);
	wpa_hexdump_buf(MSG_DEBUG, "DH: public value", pv);

	return pv;
}