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
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_options (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_OP_NO_TLSv1_1 ; 
 int /*<<< orphan*/  SSL_OP_NO_TLSv1_2 ; 
 int /*<<< orphan*/  SSLv23_method () ; 
 scalar_t__ disable_tls_11_and_12 ; 
 int /*<<< orphan*/ * the_ssl_ctx ; 

SSL_CTX *
get_ssl_ctx(void)
{
	if (the_ssl_ctx)
		return the_ssl_ctx;
	the_ssl_ctx = SSL_CTX_new(SSLv23_method());
	if (!the_ssl_ctx)
		return NULL;
	if (disable_tls_11_and_12) {
#ifdef SSL_OP_NO_TLSv1_2
		SSL_CTX_set_options(the_ssl_ctx, SSL_OP_NO_TLSv1_2);
#endif
#ifdef SSL_OP_NO_TLSv1_1
		SSL_CTX_set_options(the_ssl_ctx, SSL_OP_NO_TLSv1_1);
#endif
	}
	return the_ssl_ctx;
}