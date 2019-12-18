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
struct TYPE_4__ {int depth; int reason; char const* reason_txt; struct wpabuf* cert; } ;
struct TYPE_3__ {char* subject; } ;
union tls_event_data {TYPE_2__ cert_fail; TYPE_1__ peer_cert; } ;
typedef  int /*<<< orphan*/  subject ;
struct x509_certificate {int /*<<< orphan*/  cert_len; int /*<<< orphan*/  cert_start; int /*<<< orphan*/  subject; } ;
struct wpabuf {int dummy; } ;
struct tlsv1_client {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* event_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tls_event_data*) ;} ;
typedef  int /*<<< orphan*/  ev ;
typedef  enum tls_fail_reason { ____Placeholder_tls_fail_reason } tls_fail_reason ;

/* Variables and functions */
 int /*<<< orphan*/  TLS_CERT_CHAIN_FAILURE ; 
 int /*<<< orphan*/  os_memset (union tls_event_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tls_event_data*) ; 
 struct wpabuf* wpabuf_alloc_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  x509_name_string (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void tls_cert_chain_failure_event(struct tlsv1_client *conn, int depth,
					 struct x509_certificate *cert,
					 enum tls_fail_reason reason,
					 const char *reason_txt)
{
	struct wpabuf *cert_buf = NULL;
	union tls_event_data ev;
	char subject[128];

	if (!conn->event_cb || !cert)
		return;

	os_memset(&ev, 0, sizeof(ev));
	ev.cert_fail.depth = depth;
	x509_name_string(&cert->subject, subject, sizeof(subject));
	ev.peer_cert.subject = subject;
	ev.cert_fail.reason = reason;
	ev.cert_fail.reason_txt = reason_txt;
	cert_buf = wpabuf_alloc_copy(cert->cert_start,
				     cert->cert_len);
	ev.cert_fail.cert = cert_buf;
	conn->event_cb(conn->cb_ctx, TLS_CERT_CHAIN_FAILURE, &ev);
	wpabuf_free(cert_buf);
}