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
 int /*<<< orphan*/  SSL_FILETYPE_PEM ; 
 scalar_t__ wolfSSL_SetTmpDH_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ wolfSSL_SetTmpDH_file (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wolfSSL_set_accept_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int tls_connection_dh(struct tls_connection *conn, const char *dh_file,
			     const u8 *dh_blob, size_t blob_len)
{
	if (!dh_file && !dh_blob)
		return 0;

	wolfSSL_set_accept_state(conn->ssl);

	if (dh_blob) {
		if (wolfSSL_SetTmpDH_buffer(conn->ssl, dh_blob, blob_len,
					    SSL_FILETYPE_ASN1) < 0) {
			wpa_printf(MSG_INFO, "SSL: use DH DER blob failed");
			return -1;
		}
		wpa_printf(MSG_DEBUG, "SSL: use DH blob OK");
		return 0;
	}

	if (dh_file) {
		wpa_printf(MSG_INFO, "SSL: use DH PEM file: %s", dh_file);
		if (wolfSSL_SetTmpDH_file(conn->ssl, dh_file,
					  SSL_FILETYPE_PEM) < 0) {
			wpa_printf(MSG_INFO, "SSL: use DH PEM file failed");
			if (wolfSSL_SetTmpDH_file(conn->ssl, dh_file,
						  SSL_FILETYPE_ASN1) < 0) {
				wpa_printf(MSG_INFO,
					   "SSL: use DH DER file failed");
				return -1;
			}
		}
		wpa_printf(MSG_DEBUG, "SSL: use DH file OK");
		return 0;
	}

	return 0;
}