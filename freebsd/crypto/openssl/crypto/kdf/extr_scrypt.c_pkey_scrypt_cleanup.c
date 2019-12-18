#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* data; } ;
struct TYPE_5__ {int /*<<< orphan*/  pass_len; int /*<<< orphan*/  pass; int /*<<< orphan*/  salt_len; int /*<<< orphan*/  salt; } ;
typedef  TYPE_1__ SCRYPT_PKEY_CTX ;
typedef  TYPE_2__ EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_clear_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

__attribute__((used)) static void pkey_scrypt_cleanup(EVP_PKEY_CTX *ctx)
{
    SCRYPT_PKEY_CTX *kctx = ctx->data;

    OPENSSL_clear_free(kctx->salt, kctx->salt_len);
    OPENSSL_clear_free(kctx->pass, kctx->pass_len);
    OPENSSL_free(kctx);
}