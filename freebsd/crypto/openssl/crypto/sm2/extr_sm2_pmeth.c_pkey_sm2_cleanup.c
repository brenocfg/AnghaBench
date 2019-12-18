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
struct TYPE_5__ {struct TYPE_5__* id; int /*<<< orphan*/  gen_group; } ;
typedef  TYPE_1__ SM2_PKEY_CTX ;
typedef  TYPE_2__ EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EC_GROUP_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

__attribute__((used)) static void pkey_sm2_cleanup(EVP_PKEY_CTX *ctx)
{
    SM2_PKEY_CTX *smctx = ctx->data;

    if (smctx != NULL) {
        EC_GROUP_free(smctx->gen_group);
        OPENSSL_free(smctx->id);
        OPENSSL_free(smctx);
        ctx->data = NULL;
    }
}