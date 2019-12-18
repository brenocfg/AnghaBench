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
struct tls_connection {int /*<<< orphan*/  ssl; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  SSL_FILETYPE_ASN1 ; 
 scalar_t__ wolfSSL_use_certificate_chain_buffer_format (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ wolfSSL_use_certificate_chain_file (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ wolfSSL_use_certificate_chain_file_format (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tls_connection_client_cert(struct tls_connection *conn,
				      const char *client_cert,
				      const u8 *client_cert_blob,
				      size_t blob_len)
{
	if (!client_cert && !client_cert_blob)
		return 0;

	if (client_cert_blob) {
		if (wolfSSL_use_certificate_chain_buffer_format(
			    conn->ssl, client_cert_blob, blob_len,
			    SSL_FILETYPE_ASN1) < 0) {
			wpa_printf(MSG_INFO,
				   "SSL: use client cert DER blob failed");
			return -1;
		}
		wpa_printf(MSG_DEBUG, "SSL: use client cert blob OK");
		return 0;
	}

	if (client_cert) {
		if (wolfSSL_use_certificate_chain_file(conn->ssl,
						       client_cert) < 0) {
			wpa_printf(MSG_INFO,
				   "SSL: use client cert PEM file failed");
			if (wolfSSL_use_certificate_chain_file_format(
				    conn->ssl, client_cert,
				    SSL_FILETYPE_ASN1) < 0) {
				wpa_printf(MSG_INFO,
					   "SSL: use client cert DER file failed");
				return -1;
			}
		}
		wpa_printf(MSG_DEBUG, "SSL: use client cert file OK");
		return 0;
	}

	return 0;
}