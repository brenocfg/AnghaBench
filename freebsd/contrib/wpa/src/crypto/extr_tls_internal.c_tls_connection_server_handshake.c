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
struct tls_connection {int /*<<< orphan*/ * server; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 scalar_t__ tlsv1_server_established (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tlsv1_server_handshake (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 struct wpabuf* wpabuf_alloc (int /*<<< orphan*/ ) ; 
 struct wpabuf* wpabuf_alloc_ext_data (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf const*) ; 

struct wpabuf * tls_connection_server_handshake(void *tls_ctx,
						struct tls_connection *conn,
						const struct wpabuf *in_data,
						struct wpabuf **appl_data)
{
#ifdef CONFIG_TLS_INTERNAL_SERVER
	u8 *res;
	size_t res_len;
	struct wpabuf *out;

	if (conn->server == NULL)
		return NULL;

	if (appl_data)
		*appl_data = NULL;

	res = tlsv1_server_handshake(conn->server, wpabuf_head(in_data),
				     wpabuf_len(in_data), &res_len);
	if (res == NULL && tlsv1_server_established(conn->server))
		return wpabuf_alloc(0);
	if (res == NULL)
		return NULL;
	out = wpabuf_alloc_ext_data(res, res_len);
	if (out == NULL) {
		os_free(res);
		return NULL;
	}

	return out;
#else /* CONFIG_TLS_INTERNAL_SERVER */
	return NULL;
#endif /* CONFIG_TLS_INTERNAL_SERVER */
}