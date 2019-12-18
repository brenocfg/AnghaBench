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
struct TYPE_4__ {int depth; char const* subject; int reason; char const* reason_txt; struct wpabuf* cert; } ;
union tls_event_data {TYPE_1__ cert_fail; } ;
struct wpabuf {int dummy; } ;
struct tls_global {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* event_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tls_event_data*) ;} ;
struct tls_connection {struct tls_global* global; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ gnutls_datum_t ;
typedef  int /*<<< orphan*/  ev ;
typedef  enum tls_fail_reason { ____Placeholder_tls_fail_reason } tls_fail_reason ;

/* Variables and functions */
 int /*<<< orphan*/  TLS_CERT_CHAIN_FAILURE ; 
 int /*<<< orphan*/  os_memset (union tls_event_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tls_event_data*) ; 
 struct wpabuf* wpabuf_alloc_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 

__attribute__((used)) static void gnutls_tls_fail_event(struct tls_connection *conn,
				  const gnutls_datum_t *cert, int depth,
				  const char *subject, const char *err_str,
				  enum tls_fail_reason reason)
{
	union tls_event_data ev;
	struct tls_global *global = conn->global;
	struct wpabuf *cert_buf = NULL;

	if (global->event_cb == NULL)
		return;

	os_memset(&ev, 0, sizeof(ev));
	ev.cert_fail.depth = depth;
	ev.cert_fail.subject = subject ? subject : "";
	ev.cert_fail.reason = reason;
	ev.cert_fail.reason_txt = err_str;
	if (cert) {
		cert_buf = wpabuf_alloc_copy(cert->data, cert->size);
		ev.cert_fail.cert = cert_buf;
	}
	global->event_cb(global->cb_ctx, TLS_CERT_CHAIN_FAILURE, &ev);
	wpabuf_free(cert_buf);
}