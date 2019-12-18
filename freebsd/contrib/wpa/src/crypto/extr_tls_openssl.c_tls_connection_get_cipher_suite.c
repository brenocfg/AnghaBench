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
typedef  int u16 ;
struct tls_connection {int /*<<< orphan*/  ssl; } ;
typedef  int /*<<< orphan*/  SSL_CIPHER ;

/* Variables and functions */
 int SSL_CIPHER_get_id (int /*<<< orphan*/  const*) ; 
 int SSL_CIPHER_get_protocol_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * SSL_get_current_cipher (int /*<<< orphan*/ ) ; 

u16 tls_connection_get_cipher_suite(struct tls_connection *conn)
{
	const SSL_CIPHER *cipher;

	cipher = SSL_get_current_cipher(conn->ssl);
	if (!cipher)
		return 0;
#if OPENSSL_VERSION_NUMBER >= 0x10101000L && !defined(LIBRESSL_VERSION_NUMBER)
	return SSL_CIPHER_get_protocol_id(cipher);
#else
	return SSL_CIPHER_get_id(cipher) & 0xFFFF;
#endif
}