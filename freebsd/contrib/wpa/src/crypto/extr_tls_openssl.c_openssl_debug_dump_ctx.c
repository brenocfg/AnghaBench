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
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  openssl_debug_dump_certificate_chains (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  openssl_debug_dump_cipher_list (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void openssl_debug_dump_ctx(SSL_CTX *ssl_ctx)
{
	openssl_debug_dump_cipher_list(ssl_ctx);
	openssl_debug_dump_certificate_chains(ssl_ctx);
}