#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int hash_len; int depth; char const* subject; char* serial_num; char** altsubject; int num_altsubject; int /*<<< orphan*/  tod; int /*<<< orphan*/ * hash; struct wpabuf* cert; } ;
union tls_event_data {TYPE_3__ peer_cert; } ;
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct tls_context {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* event_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tls_event_data*) ;scalar_t__ cert_in_cb; } ;
struct tls_connection {int flags; scalar_t__ cert_probe; struct tls_context* context; } ;
typedef  scalar_t__ stack_index_t ;
typedef  int /*<<< orphan*/  serial_num ;
typedef  int /*<<< orphan*/  hash ;
typedef  int /*<<< orphan*/  ev ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_7__ {TYPE_1__* ia5; } ;
struct TYPE_9__ {int type; TYPE_2__ d; } ;
struct TYPE_6__ {int length; char* data; } ;
typedef  TYPE_4__ GENERAL_NAME ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_get0_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_STRING_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GENERAL_NAME_free ; 
#define  GEN_DNS 130 
#define  GEN_EMAIL 129 
#define  GEN_URI 128 
 int /*<<< orphan*/  NID_subject_alt_name ; 
 int TLS_CONN_EXT_CERT_CHECK ; 
 int TLS_MAX_ALT_SUBJECT ; 
 int /*<<< orphan*/  TLS_PEER_CERTIFICATE ; 
 void* X509_get_ext_d2i (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_get_serialNumber (int /*<<< orphan*/ *) ; 
 struct wpabuf* get_x509_cert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  openssl_cert_tod (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (scalar_t__) ; 
 int /*<<< orphan*/  os_memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  os_memset (union tls_event_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sha256_vector (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ sk_GENERAL_NAME_num (void*) ; 
 int /*<<< orphan*/  sk_GENERAL_NAME_pop_free (void*,int /*<<< orphan*/ ) ; 
 TYPE_4__* sk_GENERAL_NAME_value (void*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tls_event_data*) ; 
 int /*<<< orphan*/  wpa_snprintf_hex_uppercase (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/ * wpabuf_head (struct wpabuf*) ; 
 size_t wpabuf_len (struct wpabuf*) ; 

__attribute__((used)) static void openssl_tls_cert_event(struct tls_connection *conn,
				   X509 *err_cert, int depth,
				   const char *subject)
{
	struct wpabuf *cert = NULL;
	union tls_event_data ev;
	struct tls_context *context = conn->context;
	char *altsubject[TLS_MAX_ALT_SUBJECT];
	int alt, num_altsubject = 0;
	GENERAL_NAME *gen;
	void *ext;
	stack_index_t i;
	ASN1_INTEGER *ser;
	char serial_num[128];
#ifdef CONFIG_SHA256
	u8 hash[32];
#endif /* CONFIG_SHA256 */

	if (context->event_cb == NULL)
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

	ser = X509_get_serialNumber(err_cert);
	if (ser) {
		wpa_snprintf_hex_uppercase(serial_num, sizeof(serial_num),
					   ASN1_STRING_get0_data(ser),
					   ASN1_STRING_length(ser));
		ev.peer_cert.serial_num = serial_num;
	}

	ext = X509_get_ext_d2i(err_cert, NID_subject_alt_name, NULL, NULL);
	for (i = 0; ext && i < sk_GENERAL_NAME_num(ext); i++) {
		char *pos;

		if (num_altsubject == TLS_MAX_ALT_SUBJECT)
			break;
		gen = sk_GENERAL_NAME_value(ext, i);
		if (gen->type != GEN_EMAIL &&
		    gen->type != GEN_DNS &&
		    gen->type != GEN_URI)
			continue;

		pos = os_malloc(10 + gen->d.ia5->length + 1);
		if (pos == NULL)
			break;
		altsubject[num_altsubject++] = pos;

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

		os_memcpy(pos, gen->d.ia5->data, gen->d.ia5->length);
		pos += gen->d.ia5->length;
		*pos = '\0';
	}
	sk_GENERAL_NAME_pop_free(ext, GENERAL_NAME_free);

	for (alt = 0; alt < num_altsubject; alt++)
		ev.peer_cert.altsubject[alt] = altsubject[alt];
	ev.peer_cert.num_altsubject = num_altsubject;

	ev.peer_cert.tod = openssl_cert_tod(err_cert);

	context->event_cb(context->cb_ctx, TLS_PEER_CERTIFICATE, &ev);
	wpabuf_free(cert);
	for (alt = 0; alt < num_altsubject; alt++)
		os_free(altsubject[alt]);
}