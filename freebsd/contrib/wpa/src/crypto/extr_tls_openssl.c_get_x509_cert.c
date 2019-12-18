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
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 int i2d_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/ * wpabuf_put (struct wpabuf*,int) ; 

__attribute__((used)) static struct wpabuf * get_x509_cert(X509 *cert)
{
	struct wpabuf *buf;
	u8 *tmp;

	int cert_len = i2d_X509(cert, NULL);
	if (cert_len <= 0)
		return NULL;

	buf = wpabuf_alloc(cert_len);
	if (buf == NULL)
		return NULL;

	tmp = wpabuf_put(buf, cert_len);
	i2d_X509(cert, &tmp);
	return buf;
}