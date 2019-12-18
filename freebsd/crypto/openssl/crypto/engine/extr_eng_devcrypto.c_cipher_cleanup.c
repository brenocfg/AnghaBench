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
struct cipher_ctx {int /*<<< orphan*/  sess; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 scalar_t__ EVP_CIPHER_CTX_get_cipher_data (int /*<<< orphan*/ *) ; 
 int clean_devcrypto_session (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cipher_cleanup(EVP_CIPHER_CTX *ctx)
{
    struct cipher_ctx *cipher_ctx =
        (struct cipher_ctx *)EVP_CIPHER_CTX_get_cipher_data(ctx);

    return clean_devcrypto_session(&cipher_ctx->sess);
}