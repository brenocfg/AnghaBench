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
typedef  int /*<<< orphan*/  const u8 ;
struct x509_certificate {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/  const*) ; 
 scalar_t__ os_readfile (char const*,size_t*) ; 
 int tlsv1_add_cert (struct x509_certificate**,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int tlsv1_set_cert_chain(struct x509_certificate **chain,
				const char *cert, const u8 *cert_blob,
				size_t cert_blob_len)
{
	if (cert_blob)
		return tlsv1_add_cert(chain, cert_blob, cert_blob_len);

	if (cert) {
		u8 *buf;
		size_t len;
		int ret;

		buf = (u8 *) os_readfile(cert, &len);
		if (buf == NULL) {
			wpa_printf(MSG_INFO, "TLSv1: Failed to read '%s'",
				   cert);
			return -1;
		}

		ret = tlsv1_add_cert(chain, buf, len);
		os_free(buf);
		return ret;
	}

	return 0;
}