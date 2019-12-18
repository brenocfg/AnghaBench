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
struct tls_connection {int /*<<< orphan*/  ssl; } ;
typedef  int /*<<< orphan*/  WOLFSSL_CIPHER ;

/* Variables and functions */
 scalar_t__ os_strcmp (char const*,char*) ; 
 int /*<<< orphan*/  os_strlcpy (char*,char const*,size_t) ; 
 char* wolfSSL_CIPHER_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wolfSSL_get_current_cipher (int /*<<< orphan*/ ) ; 

int tls_get_cipher(void *tls_ctx, struct tls_connection *conn,
		   char *buf, size_t buflen)
{
	WOLFSSL_CIPHER *cipher;
	const char *name;

	if (!conn || !conn->ssl)
		return -1;

	cipher = wolfSSL_get_current_cipher(conn->ssl);
	if (!cipher)
		return -1;

	name = wolfSSL_CIPHER_get_name(cipher);
	if (!name)
		return -1;

	if (os_strcmp(name, "SSL_RSA_WITH_RC4_128_SHA") == 0)
		os_strlcpy(buf, "RC4-SHA", buflen);
	else if (os_strcmp(name, "TLS_RSA_WITH_AES_128_CBC_SHA") == 0)
		os_strlcpy(buf, "AES128-SHA", buflen);
	else if (os_strcmp(name, "TLS_DHE_RSA_WITH_AES_128_CBC_SHA") == 0)
		os_strlcpy(buf, "DHE-RSA-AES128-SHA", buflen);
	else if (os_strcmp(name, "TLS_DH_anon_WITH_AES_128_CBC_SHA") == 0)
		os_strlcpy(buf, "ADH-AES128-SHA", buflen);
	else if (os_strcmp(name, "TLS_DHE_RSA_WITH_AES_256_CBC_SHA") == 0)
		os_strlcpy(buf, "DHE-RSA-AES256-SHA", buflen);
	else if (os_strcmp(name, "TLS_RSA_WITH_AES_256_CBC_SHA") == 0)
		os_strlcpy(buf, "AES256-SHA", buflen);
	else
		os_strlcpy(buf, name, buflen);

	return 0;
}