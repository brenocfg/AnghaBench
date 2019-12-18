#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int keygen_info_count; int /*<<< orphan*/  keygen_info; TYPE_1__* data; } ;
struct TYPE_6__ {int nbits; int min_saltlen; int /*<<< orphan*/  gentmp; int /*<<< orphan*/  saltlen; int /*<<< orphan*/  pad_mode; int /*<<< orphan*/  primes; } ;
typedef  TYPE_1__ RSA_PKEY_CTX ;
typedef  TYPE_2__ EVP_PKEY_CTX ;

/* Variables and functions */
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  RSA_DEFAULT_PRIME_NUM ; 
 int /*<<< orphan*/  RSA_PKCS1_PADDING ; 
 int /*<<< orphan*/  RSA_PKCS1_PSS_PADDING ; 
 int /*<<< orphan*/  RSA_PSS_SALTLEN_AUTO ; 
 scalar_t__ pkey_ctx_is_pss (TYPE_2__*) ; 

__attribute__((used)) static int pkey_rsa_init(EVP_PKEY_CTX *ctx)
{
    RSA_PKEY_CTX *rctx = OPENSSL_zalloc(sizeof(*rctx));

    if (rctx == NULL)
        return 0;
    rctx->nbits = 2048;
    rctx->primes = RSA_DEFAULT_PRIME_NUM;
    if (pkey_ctx_is_pss(ctx))
        rctx->pad_mode = RSA_PKCS1_PSS_PADDING;
    else
        rctx->pad_mode = RSA_PKCS1_PADDING;
    /* Maximum for sign, auto for verify */
    rctx->saltlen = RSA_PSS_SALTLEN_AUTO;
    rctx->min_saltlen = -1;
    ctx->data = rctx;
    ctx->keygen_info = rctx->gentmp;
    ctx->keygen_info_count = 2;

    return 1;
}