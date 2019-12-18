#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int hash_len; int depth; char const* subject; char** altsubject; int num_altsubject; int /*<<< orphan*/ * hash; struct wpabuf* cert; } ;
union tls_event_data {TYPE_1__ peer_cert; } ;
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct tls_context {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* event_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tls_event_data*) ;scalar_t__ cert_in_cb; } ;
struct tls_connection {int flags; scalar_t__ cert_probe; struct tls_context* context; } ;
typedef  int /*<<< orphan*/  hash ;
typedef  int /*<<< orphan*/  ev ;
typedef  int /*<<< orphan*/  WOLFSSL_X509 ;
struct TYPE_5__ {int type; char* obj; } ;
typedef  TYPE_2__ WOLFSSL_ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ALT_NAMES_OID ; 
#define  GEN_DNS 130 
#define  GEN_EMAIL 129 
#define  GEN_URI 128 
 int TLS_CONN_EXT_CERT_CHECK ; 
 int TLS_MAX_ALT_SUBJECT ; 
 int /*<<< orphan*/  TLS_PEER_CERTIFICATE ; 
 struct wpabuf* get_x509_cert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (int) ; 
 int /*<<< orphan*/  os_memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  os_memset (union tls_event_data*,int /*<<< orphan*/ ,int) ; 
 int os_strlen (char*) ; 
 scalar_t__ sha256_vector (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tls_event_data*) ; 
 void* wolfSSL_X509_get_ext_d2i (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wolfSSL_sk_ASN1_OBJECT_free (void*) ; 
 int wolfSSL_sk_num (void*) ; 
 TYPE_2__* wolfSSL_sk_value (void*,int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/ * wpabuf_head (struct wpabuf*) ; 
 size_t wpabuf_len (struct wpabuf*) ; 

__attribute__((used)) static void wolfssl_tls_cert_event(struct tls_connection *conn,
				   WOLFSSL_X509 *err_cert, int depth,
				   const char *subject)
{
	struct wpabuf *cert = NULL;
	union tls_event_data ev;
	struct tls_context *context = conn->context;
	char *alt_subject[TLS_MAX_ALT_SUBJECT];
	int alt, num_alt_subject = 0;
	WOLFSSL_ASN1_OBJECT *gen;
	void *ext;
	int i;
#ifdef CONFIG_SHA256
	u8 hash[32];
#endif /* CONFIG_SHA256 */

	if (!context->event_cb)
		return;

	os_memset(&ev, 0, sizeof(ev));
	if (conn->cert_probe || (conn->flags & TLS_CONN_EXT_CERT_CHECK) ||
	    context->cert_in_cb) {
		cert = get_x509_cert(err_cert);
		ev.peer_cert.cert = cert;
	}

#ifdef CONFIG_SHA256
	if (cert) {
		const u8 *addr[1];
		size_t len[1];

		addr[0] = wpabuf_head(cert);
		len[0] = wpabuf_len(cert);
		if (sha256_vector(1, addr, len, hash) == 0) {
			ev.peer_cert.hash = hash;
			ev.peer_cert.hash_len = sizeof(hash);
		}
	}
#endif /* CONFIG_SHA256 */

	ev.peer_cert.depth = depth;
	ev.peer_cert.subject = subject;

	ext = wolfSSL_X509_get_ext_d2i(err_cert, ALT_NAMES_OID, NULL, NULL);
	for (i = 0; ext && i < wolfSSL_sk_num(ext); i++) {
		char *pos;

		if (num_alt_subject == TLS_MAX_ALT_SUBJECT)
			break;
		gen = wolfSSL_sk_value((void *) ext, i);
		if (gen->type != GEN_EMAIL &&
		    gen->type != GEN_DNS &&
		    gen->type != GEN_URI)
			continue;

		pos = os_malloc(10 + os_strlen((char *) gen->obj) + 1);
		if (!pos)
			break;
		alt_subject[num_alt_subject++] = pos;

		switch (gen->type) {
		case GEN_EMAIL:
			os_memcpy(pos, "EMAIL:", 6);
			pos += 6;
			break;
		case GEN_DNS:
			os_memcpy(pos, "DNS:", 4);
			pos += 4;
			break;
		case GEN_URI:
			os_memcpy(pos, "URI:", 4);
			pos += 4;
			break;
		}

		os_memcpy(pos, gen->obj, os_strlen((char *)gen->obj));
		pos += os_strlen((char *)gen->obj);
		*pos = '\0';
	}
	wolfSSL_sk_ASN1_OBJECT_free(ext);

	for (alt = 0; alt < num_alt_subject; alt++)
		ev.peer_cert.altsubject[alt] = alt_subject[alt];
	ev.peer_cert.num_altsubject = num_alt_subject;

	context->event_cb(context->cb_ctx, TLS_PEER_CERTIFICATE, &ev);
	wpabuf_free(cert);
	for (alt = 0; alt < num_alt_subject; alt++)
		os_free(alt_subject[alt]);
}