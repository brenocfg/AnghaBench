#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* pmeth; int /*<<< orphan*/  operation; int /*<<< orphan*/ * app_data; int /*<<< orphan*/ * data; scalar_t__ peerkey; scalar_t__ pkey; scalar_t__ engine; } ;
struct TYPE_9__ {scalar_t__ (* copy ) (TYPE_2__*,TYPE_2__*) ;} ;
typedef  TYPE_2__ EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_init (scalar_t__) ; 
 int /*<<< orphan*/  ERR_R_ENGINE_LIB ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_F_EVP_PKEY_CTX_DUP ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (TYPE_2__*) ; 
 int /*<<< orphan*/  EVP_PKEY_up_ref (scalar_t__) ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* OPENSSL_malloc (int) ; 
 scalar_t__ stub1 (TYPE_2__*,TYPE_2__*) ; 

EVP_PKEY_CTX *EVP_PKEY_CTX_dup(EVP_PKEY_CTX *pctx)
{
    EVP_PKEY_CTX *rctx;
    if (!pctx->pmeth || !pctx->pmeth->copy)
        return NULL;
#ifndef OPENSSL_NO_ENGINE
    /* Make sure it's safe to copy a pkey context using an ENGINE */
    if (pctx->engine && !ENGINE_init(pctx->engine)) {
        EVPerr(EVP_F_EVP_PKEY_CTX_DUP, ERR_R_ENGINE_LIB);
        return 0;
    }
#endif
    rctx = OPENSSL_malloc(sizeof(*rctx));
    if (rctx == NULL) {
        EVPerr(EVP_F_EVP_PKEY_CTX_DUP, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    rctx->pmeth = pctx->pmeth;
#ifndef OPENSSL_NO_ENGINE
    rctx->engine = pctx->engine;
#endif

    if (pctx->pkey)
        EVP_PKEY_up_ref(pctx->pkey);

    rctx->pkey = pctx->pkey;

    if (pctx->peerkey)
        EVP_PKEY_up_ref(pctx->peerkey);

    rctx->peerkey = pctx->peerkey;

    rctx->data = NULL;
    rctx->app_data = NULL;
    rctx->operation = pctx->operation;

    if (pctx->pmeth->copy(rctx, pctx) > 0)
        return rctx;

    rctx->pmeth = NULL;
    EVP_PKEY_CTX_free(rctx);
    return NULL;

}