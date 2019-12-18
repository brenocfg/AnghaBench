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
struct wpabuf {int dummy; } ;
typedef  int /*<<< orphan*/  WOLFSSL_X509 ;

/* Variables and functions */
 int /*<<< orphan*/ * wolfSSL_X509_get_der (int /*<<< orphan*/ *,int*) ; 
 struct wpabuf* wpabuf_alloc_copy (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static struct wpabuf * get_x509_cert(WOLFSSL_X509 *cert)
{
	struct wpabuf *buf = NULL;
	const u8 *data;
	int cert_len;

	data = wolfSSL_X509_get_der(cert, &cert_len);
	if (!data)
		buf = wpabuf_alloc_copy(data, cert_len);

	return buf;
}