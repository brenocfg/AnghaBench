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
struct TYPE_2__ {int /*<<< orphan*/ * ocsp_stapling_response; } ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 char* OPENSSL_malloc (size_t) ; 
 int SSL_TLSEXT_ERR_ALERT_FATAL ; 
 int SSL_TLSEXT_ERR_OK ; 
 int /*<<< orphan*/  SSL_set_tlsext_status_ocsp_resp (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  os_memcpy (char*,char*,size_t) ; 
 char* os_readfile (int /*<<< orphan*/ *,size_t*) ; 
 TYPE_1__* tls_global ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ocsp_status_cb(SSL *s, void *arg)
{
	char *tmp;
	char *resp;
	size_t len;

	if (tls_global->ocsp_stapling_response == NULL) {
		wpa_printf(MSG_DEBUG, "OpenSSL: OCSP status callback - no response configured");
		return SSL_TLSEXT_ERR_OK;
	}

	resp = os_readfile(tls_global->ocsp_stapling_response, &len);
	if (resp == NULL) {
		wpa_printf(MSG_DEBUG, "OpenSSL: OCSP status callback - could not read response file");
		/* TODO: Build OCSPResponse with responseStatus = internalError
		 */
		return SSL_TLSEXT_ERR_OK;
	}
	wpa_printf(MSG_DEBUG, "OpenSSL: OCSP status callback - send cached response");
	tmp = OPENSSL_malloc(len);
	if (tmp == NULL) {
		os_free(resp);
		return SSL_TLSEXT_ERR_ALERT_FATAL;
	}

	os_memcpy(tmp, resp, len);
	os_free(resp);
	SSL_set_tlsext_status_ocsp_resp(s, tmp, len);

	return SSL_TLSEXT_ERR_OK;
}