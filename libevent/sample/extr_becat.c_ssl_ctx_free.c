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
struct ssl_context {int /*<<< orphan*/  cert; int /*<<< orphan*/  pkey; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ssl_ctx_free(struct ssl_context *ssl)
{
	SSL_CTX_free(ssl->ctx);
	EVP_PKEY_free(ssl->pkey);
	X509_free(ssl->cert);
}