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
struct tls_connection {int ca_cert_verify; int cert_probe; int server_cert_only; int /*<<< orphan*/  srv_cert_hash; int /*<<< orphan*/  ssl; } ;
typedef  int /*<<< orphan*/  WOLFSSL_X509_STORE ;
typedef  int /*<<< orphan*/  WOLFSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  SSL_FILETYPE_ASN1 ; 
 scalar_t__ SSL_SUCCESS ; 
 int /*<<< orphan*/  SSL_VERIFY_PEER ; 
 scalar_t__ hexstr2bin (char const*,int /*<<< orphan*/ ,int) ; 
 int os_strlen (char const*) ; 
 scalar_t__ os_strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  tls_verify_cb ; 
 scalar_t__ wolfSSL_CTX_der_load_verify_locations (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ wolfSSL_CTX_load_verify_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ wolfSSL_CTX_load_verify_locations (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  wolfSSL_CTX_set_cert_store (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wolfSSL_X509_STORE_new () ; 
 int /*<<< orphan*/  wolfSSL_set_verify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int tls_connection_ca_cert(void *tls_ctx, struct tls_connection *conn,
				  const char *ca_cert,
				  const u8 *ca_cert_blob, size_t blob_len,
				  const char *ca_path)
{
	WOLFSSL_CTX *ctx = tls_ctx;

	wolfSSL_set_verify(conn->ssl, SSL_VERIFY_PEER, tls_verify_cb);
	conn->ca_cert_verify = 1;

	if (ca_cert && os_strncmp(ca_cert, "probe://", 8) == 0) {
		wpa_printf(MSG_DEBUG,
			   "wolfSSL: Probe for server certificate chain");
		conn->cert_probe = 1;
		conn->ca_cert_verify = 0;
		return 0;
	}

	if (ca_cert && os_strncmp(ca_cert, "hash://", 7) == 0) {
#ifdef CONFIG_SHA256
		const char *pos = ca_cert + 7;

		if (os_strncmp(pos, "server/sha256/", 14) != 0) {
			wpa_printf(MSG_DEBUG,
				   "wolfSSL: Unsupported ca_cert hash value '%s'",
				   ca_cert);
			return -1;
		}
		pos += 14;
		if (os_strlen(pos) != 32 * 2) {
			wpa_printf(MSG_DEBUG,
				   "wolfSSL: Unexpected SHA256 hash length in ca_cert '%s'",
				   ca_cert);
			return -1;
		}
		if (hexstr2bin(pos, conn->srv_cert_hash, 32) < 0) {
			wpa_printf(MSG_DEBUG,
				   "wolfSSL: Invalid SHA256 hash value in ca_cert '%s'",
				   ca_cert);
			return -1;
		}
		conn->server_cert_only = 1;
		wpa_printf(MSG_DEBUG,
			   "wolfSSL: Checking only server certificate match");
		return 0;
#else /* CONFIG_SHA256 */
		wpa_printf(MSG_INFO,
			   "No SHA256 included in the build - cannot validate server certificate hash");
		return -1;
#endif /* CONFIG_SHA256 */
	}

	if (ca_cert_blob) {
		if (wolfSSL_CTX_load_verify_buffer(ctx, ca_cert_blob, blob_len,
						   SSL_FILETYPE_ASN1) !=
		    SSL_SUCCESS) {
			wpa_printf(MSG_INFO, "SSL: failed to load CA blob");
			return -1;
		}
		wpa_printf(MSG_DEBUG, "SSL: use CA cert blob OK");
		return 0;
	}

	if (ca_cert || ca_path) {
		WOLFSSL_X509_STORE *cm = wolfSSL_X509_STORE_new();

		if (!cm) {
			wpa_printf(MSG_INFO,
				   "SSL: failed to create certificate store");
			return -1;
		}
		wolfSSL_CTX_set_cert_store(ctx, cm);

		if (wolfSSL_CTX_load_verify_locations(ctx, ca_cert, ca_path) !=
		    SSL_SUCCESS) {
			wpa_printf(MSG_INFO,
				   "SSL: failed to load ca_cert as PEM");

			if (!ca_cert)
				return -1;

			if (wolfSSL_CTX_der_load_verify_locations(
				    ctx, ca_cert, SSL_FILETYPE_ASN1) !=
			    SSL_SUCCESS) {
				wpa_printf(MSG_INFO,
					   "SSL: failed to load ca_cert as DER");
				return -1;
			}
		}
		return 0;
	}

	conn->ca_cert_verify = 0;
	return 0;
}