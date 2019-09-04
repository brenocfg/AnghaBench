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
 long SSL_CTX_get_options (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_options (int /*<<< orphan*/ *,long) ; 
 long SSL_OP_NO_SSLv2 ; 
 long SSL_OP_NO_SSLv3 ; 
 int /*<<< orphan*/  SSLv23_client_method () ; 

__attribute__((used)) static SSL_CTX *create_ssl_ctx(void)
{
    long options;
    SSL_CTX *ctx = SSL_CTX_new(SSLv23_client_method());
    options = SSL_CTX_get_options(ctx) | SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3;
#ifdef SSL_OP_NO_RENEGOTIATION
    /* introduced in openssl 1.1.0h */
    options |= SSL_OP_NO_RENEGOTIATION;
#endif
    SSL_CTX_set_options(ctx, options);
    return ctx;
}