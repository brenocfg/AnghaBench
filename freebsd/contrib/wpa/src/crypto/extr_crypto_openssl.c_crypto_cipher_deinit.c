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
struct crypto_cipher {int /*<<< orphan*/  dec; int /*<<< orphan*/  enc; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct crypto_cipher*) ; 

void crypto_cipher_deinit(struct crypto_cipher *ctx)
{
	EVP_CIPHER_CTX_free(ctx->enc);
	EVP_CIPHER_CTX_free(ctx->dec);
	os_free(ctx);
}