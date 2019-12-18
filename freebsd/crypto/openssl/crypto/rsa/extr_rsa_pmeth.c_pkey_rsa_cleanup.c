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
struct TYPE_5__ {struct TYPE_5__* oaep_label; struct TYPE_5__* tbuf; int /*<<< orphan*/  pub_exp; } ;
typedef  TYPE_1__ RSA_PKEY_CTX ;
typedef  TYPE_2__ EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

__attribute__((used)) static void pkey_rsa_cleanup(EVP_PKEY_CTX *ctx)
{
    RSA_PKEY_CTX *rctx = ctx->data;
    if (rctx) {
        BN_free(rctx->pub_exp);
        OPENSSL_free(rctx->tbuf);
        OPENSSL_free(rctx->oaep_label);
        OPENSSL_free(rctx);
    }
}