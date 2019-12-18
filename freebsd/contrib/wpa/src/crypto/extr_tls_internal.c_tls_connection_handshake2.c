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
struct tls_connection {int /*<<< orphan*/ * client; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tlsv1_client_handshake (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ **,size_t*,int*) ; 
 struct wpabuf* wpabuf_alloc_ext_data (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * wpabuf_head (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf const*) ; 

struct wpabuf * tls_connection_handshake2(void *tls_ctx,
					  struct tls_connection *conn,
					  const struct wpabuf *in_data,
					  struct wpabuf **appl_data,
					  int *need_more_data)
{
#ifdef CONFIG_TLS_INTERNAL_CLIENT
	u8 *res, *ad;
	size_t res_len, ad_len;
	struct wpabuf *out;

	if (conn->client == NULL)
		return NULL;

	ad = NULL;
	res = tlsv1_client_handshake(conn->client,
				     in_data ? wpabuf_head(in_data) : NULL,
				     in_data ? wpabuf_len(in_data) : 0,
				     &res_len, &ad, &ad_len, need_more_data);
	if (res == NULL)
		return NULL;
	out = wpabuf_alloc_ext_data(res, res_len);
	if (out == NULL) {
		os_free(res);
		os_free(ad);
		return NULL;
	}
	if (appl_data) {
		if (ad) {
			*appl_data = wpabuf_alloc_ext_data(ad, ad_len);
			if (*appl_data == NULL)
				os_free(ad);
		} else
			*appl_data = NULL;
	} else
		os_free(ad);

	return out;
#else /* CONFIG_TLS_INTERNAL_CLIENT */
	return NULL;
#endif /* CONFIG_TLS_INTERNAL_CLIENT */
}