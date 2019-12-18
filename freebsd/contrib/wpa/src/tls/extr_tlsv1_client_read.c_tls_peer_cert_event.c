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
struct TYPE_4__ {int hash_len; int depth; char* subject; int /*<<< orphan*/ * hash; struct wpabuf* cert; } ;
union tls_event_data {TYPE_2__ peer_cert; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  subject ;
struct x509_certificate {int /*<<< orphan*/  subject; int /*<<< orphan*/  cert_len; int /*<<< orphan*/  cert_start; } ;
struct wpabuf {int dummy; } ;
struct tlsv1_client {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* event_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tls_event_data*) ;scalar_t__ cert_in_cb; TYPE_1__* cred; } ;
typedef  int /*<<< orphan*/  hash ;
typedef  int /*<<< orphan*/  ev ;
struct TYPE_3__ {scalar_t__ cert_probe; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLS_PEER_CERTIFICATE ; 
 int /*<<< orphan*/  os_memset (union tls_event_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sha256_vector (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tls_event_data*) ; 
 struct wpabuf* wpabuf_alloc_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/ * wpabuf_head (struct wpabuf*) ; 
 size_t wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  x509_name_string (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void tls_peer_cert_event(struct tlsv1_client *conn, int depth,
				struct x509_certificate *cert)
{
	union tls_event_data ev;
	struct wpabuf *cert_buf = NULL;
#ifdef CONFIG_SHA256
	u8 hash[32];
#endif /* CONFIG_SHA256 */
	char subject[128];

	if (!conn->event_cb)
		return;

	os_memset(&ev, 0, sizeof(ev));
	if ((conn->cred && conn->cred->cert_probe) || conn->cert_in_cb) {
		cert_buf = wpabuf_alloc_copy(cert->cert_start,
					     cert->cert_len);
		ev.peer_cert.cert = cert_buf;
	}
#ifdef CONFIG_SHA256
	if (cert_buf) {
		const u8 *addr[1];
		size_t len[1];
		addr[0] = wpabuf_head(cert_buf);
		len[0] = wpabuf_len(cert_buf);
		if (sha256_vector(1, addr, len, hash) == 0) {
			ev.peer_cert.hash = hash;
			ev.peer_cert.hash_len = sizeof(hash);
		}
	}
#endif /* CONFIG_SHA256 */

	ev.peer_cert.depth = depth;
	x509_name_string(&cert->subject, subject, sizeof(subject));
	ev.peer_cert.subject = subject;

	conn->event_cb(conn->cb_ctx, TLS_PEER_CERTIFICATE, &ev);
	wpabuf_free(cert_buf);
}