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
struct tlsv1_credentials {int server_cert_only; int cert_probe; int /*<<< orphan*/  trusted_certs; int /*<<< orphan*/  ca_cert_verify; int /*<<< orphan*/  srv_cert_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ hexstr2bin (char const*,int /*<<< orphan*/ ,int) ; 
 int os_strlen (char const*) ; 
 scalar_t__ os_strncmp (char const*,char*,int) ; 
 scalar_t__ tlsv1_set_cert_chain (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int tlsv1_set_ca_cert(struct tlsv1_credentials *cred, const char *cert,
		      const u8 *cert_blob, size_t cert_blob_len,
		      const char *path)
{
	if (cert && os_strncmp(cert, "hash://", 7) == 0) {
		const char *pos = cert + 7;
		if (os_strncmp(pos, "server/sha256/", 14) != 0) {
			wpa_printf(MSG_DEBUG,
				   "TLSv1: Unsupported ca_cert hash value '%s'",
				   cert);
			return -1;
		}
		pos += 14;
		if (os_strlen(pos) != 32 * 2) {
			wpa_printf(MSG_DEBUG,
				   "TLSv1: Unexpected SHA256 hash length in ca_cert '%s'",
				   cert);
			return -1;
		}
		if (hexstr2bin(pos, cred->srv_cert_hash, 32) < 0) {
			wpa_printf(MSG_DEBUG,
				   "TLSv1: Invalid SHA256 hash value in ca_cert '%s'",
				   cert);
			return -1;
		}
		cred->server_cert_only = 1;
		cred->ca_cert_verify = 0;
		wpa_printf(MSG_DEBUG,
			   "TLSv1: Checking only server certificate match");
		return 0;
	}

	if (cert && os_strncmp(cert, "probe://", 8) == 0) {
		cred->cert_probe = 1;
		cred->ca_cert_verify = 0;
		wpa_printf(MSG_DEBUG, "TLSv1: Only probe server certificate");
		return 0;
	}

	cred->ca_cert_verify = cert || cert_blob || path;

	if (tlsv1_set_cert_chain(&cred->trusted_certs, cert,
				 cert_blob, cert_blob_len) < 0)
		return -1;

	if (path) {
		/* TODO: add support for reading number of certificate files */
		wpa_printf(MSG_INFO, "TLSv1: Use of CA certificate directory "
			   "not yet supported");
		return -1;
	}

	return 0;
}