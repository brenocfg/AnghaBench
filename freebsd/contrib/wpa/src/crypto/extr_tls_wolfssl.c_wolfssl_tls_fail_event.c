#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int reason; int depth; char const* subject; struct wpabuf* cert; int /*<<< orphan*/  reason_txt; } ;
union tls_event_data {TYPE_1__ cert_fail; } ;
struct wpabuf {int dummy; } ;
struct tls_context {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* event_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tls_event_data*) ;} ;
struct tls_connection {struct tls_context* context; } ;
typedef  int /*<<< orphan*/  ev ;
typedef  enum tls_fail_reason { ____Placeholder_tls_fail_reason } tls_fail_reason ;
typedef  int /*<<< orphan*/  WOLFSSL_X509 ;

/* Variables and functions */
 int /*<<< orphan*/  TLS_CERT_CHAIN_FAILURE ; 
 int TLS_FAIL_UNSPECIFIED ; 
 struct wpabuf* get_x509_cert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memset (union tls_event_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tls_event_data*) ; 
 int /*<<< orphan*/  wolfssl_tls_err_string (int,char const*) ; 
 int wolfssl_tls_fail_reason (int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 

__attribute__((used)) static void wolfssl_tls_fail_event(struct tls_connection *conn,
				   WOLFSSL_X509 *err_cert, int err, int depth,
				   const char *subject, const char *err_str,
				   enum tls_fail_reason reason)
{
	union tls_event_data ev;
	struct wpabuf *cert = NULL;
	struct tls_context *context = conn->context;

	if (!context->event_cb)
		return;

	cert = get_x509_cert(err_cert);
	os_memset(&ev, 0, sizeof(ev));
	ev.cert_fail.reason = reason != TLS_FAIL_UNSPECIFIED ?
		reason : wolfssl_tls_fail_reason(err);
	ev.cert_fail.depth = depth;
	ev.cert_fail.subject = subject;
	ev.cert_fail.reason_txt = wolfssl_tls_err_string(err, err_str);
	ev.cert_fail.cert = cert;
	context->event_cb(context->cb_ctx, TLS_CERT_CHAIN_FAILURE, &ev);
	wpabuf_free(cert);
}