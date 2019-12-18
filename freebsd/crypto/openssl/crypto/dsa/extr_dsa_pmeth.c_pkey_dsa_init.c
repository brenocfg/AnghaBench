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
struct TYPE_6__ {int nbits; int qbits; int /*<<< orphan*/  gentmp; int /*<<< orphan*/ * md; int /*<<< orphan*/ * pmd; } ;
struct TYPE_5__ {int keygen_info_count; int /*<<< orphan*/  keygen_info; TYPE_2__* data; } ;
typedef  TYPE_1__ EVP_PKEY_CTX ;
typedef  TYPE_2__ DSA_PKEY_CTX ;

/* Variables and functions */
 TYPE_2__* OPENSSL_malloc (int) ; 

__attribute__((used)) static int pkey_dsa_init(EVP_PKEY_CTX *ctx)
{
    DSA_PKEY_CTX *dctx = OPENSSL_malloc(sizeof(*dctx));

    if (dctx == NULL)
        return 0;
    dctx->nbits = 2048;
    dctx->qbits = 224;
    dctx->pmd = NULL;
    dctx->md = NULL;

    ctx->data = dctx;
    ctx->keygen_info = dctx->gentmp;
    ctx->keygen_info_count = 2;

    return 1;
}