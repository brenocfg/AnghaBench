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
struct ssl_context {int /*<<< orphan*/  ctx; } ;
typedef  int /*<<< orphan*/  SSL_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_new (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * TLS_method () ; 
 int /*<<< orphan*/  ssl_ctx_free (struct ssl_context*) ; 
 int /*<<< orphan*/  ssl_init () ; 
 scalar_t__ ssl_load_cert (struct ssl_context*) ; 
 scalar_t__ ssl_load_key (struct ssl_context*) ; 

__attribute__((used)) static int ssl_ctx_init(struct ssl_context *ssl)
{
	const SSL_METHOD *method;

	ssl_init();

	method = TLS_method();
	if (!method)
		goto err;
	ssl->ctx = SSL_CTX_new(method);

	if (ssl_load_key(ssl))
		goto err;
	if (ssl_load_cert(ssl))
		goto err;

	return 0;

err:
	ssl_ctx_free(ssl);
	return 1;
}