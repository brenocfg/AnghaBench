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
struct TYPE_10__ {scalar_t__ type; int (* init ) (TYPE_1__*) ;scalar_t__ ctx_size; int /*<<< orphan*/  update; } ;
struct TYPE_9__ {int flags; TYPE_2__ const* digest; scalar_t__ pctx; int /*<<< orphan*/ * md_data; int /*<<< orphan*/  update; int /*<<< orphan*/ * engine; } ;
typedef  TYPE_1__ EVP_MD_CTX ;
typedef  TYPE_2__ const EVP_MD ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_finish (int /*<<< orphan*/ *) ; 
 TYPE_2__ const* ENGINE_get_digest (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * ENGINE_get_digest_engine (scalar_t__) ; 
 int /*<<< orphan*/  ENGINE_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_F_EVP_DIGESTINIT_EX ; 
 int /*<<< orphan*/  EVP_MD_CTX_FLAG_CLEANED ; 
 int EVP_MD_CTX_FLAG_NO_INIT ; 
 int /*<<< orphan*/  EVP_MD_CTX_clear_flags (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_CTRL_DIGESTINIT ; 
 int EVP_PKEY_CTX_ctrl (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  EVP_PKEY_OP_TYPE_SIG ; 
 int /*<<< orphan*/  EVP_R_INITIALIZATION_ERROR ; 
 int /*<<< orphan*/  EVP_R_NO_DIGEST_SET ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * OPENSSL_zalloc (scalar_t__) ; 
 int stub1 (TYPE_1__*) ; 

int EVP_DigestInit_ex(EVP_MD_CTX *ctx, const EVP_MD *type, ENGINE *impl)
{
    EVP_MD_CTX_clear_flags(ctx, EVP_MD_CTX_FLAG_CLEANED);
#ifndef OPENSSL_NO_ENGINE
    /*
     * Whether it's nice or not, "Inits" can be used on "Final"'d contexts so
     * this context may already have an ENGINE! Try to avoid releasing the
     * previous handle, re-querying for an ENGINE, and having a
     * reinitialisation, when it may all be unnecessary.
     */
    if (ctx->engine && ctx->digest &&
        (type == NULL || (type->type == ctx->digest->type)))
        goto skip_to_init;
    if (type) {
        /*
         * Ensure an ENGINE left lying around from last time is cleared (the
         * previous check attempted to avoid this if the same ENGINE and
         * EVP_MD could be used).
         */
        ENGINE_finish(ctx->engine);
        if (impl != NULL) {
            if (!ENGINE_init(impl)) {
                EVPerr(EVP_F_EVP_DIGESTINIT_EX, EVP_R_INITIALIZATION_ERROR);
                return 0;
            }
        } else {
            /* Ask if an ENGINE is reserved for this job */
            impl = ENGINE_get_digest_engine(type->type);
        }
        if (impl != NULL) {
            /* There's an ENGINE for this job ... (apparently) */
            const EVP_MD *d = ENGINE_get_digest(impl, type->type);

            if (d == NULL) {
                EVPerr(EVP_F_EVP_DIGESTINIT_EX, EVP_R_INITIALIZATION_ERROR);
                ENGINE_finish(impl);
                return 0;
            }
            /* We'll use the ENGINE's private digest definition */
            type = d;
            /*
             * Store the ENGINE functional reference so we know 'type' came
             * from an ENGINE and we need to release it when done.
             */
            ctx->engine = impl;
        } else
            ctx->engine = NULL;
    } else {
        if (!ctx->digest) {
            EVPerr(EVP_F_EVP_DIGESTINIT_EX, EVP_R_NO_DIGEST_SET);
            return 0;
        }
        type = ctx->digest;
    }
#endif
    if (ctx->digest != type) {
        if (ctx->digest && ctx->digest->ctx_size) {
            OPENSSL_clear_free(ctx->md_data, ctx->digest->ctx_size);
            ctx->md_data = NULL;
        }
        ctx->digest = type;
        if (!(ctx->flags & EVP_MD_CTX_FLAG_NO_INIT) && type->ctx_size) {
            ctx->update = type->update;
            ctx->md_data = OPENSSL_zalloc(type->ctx_size);
            if (ctx->md_data == NULL) {
                EVPerr(EVP_F_EVP_DIGESTINIT_EX, ERR_R_MALLOC_FAILURE);
                return 0;
            }
        }
    }
#ifndef OPENSSL_NO_ENGINE
 skip_to_init:
#endif
    if (ctx->pctx) {
        int r;
        r = EVP_PKEY_CTX_ctrl(ctx->pctx, -1, EVP_PKEY_OP_TYPE_SIG,
                              EVP_PKEY_CTRL_DIGESTINIT, 0, ctx);
        if (r <= 0 && (r != -2))
            return 0;
    }
    if (ctx->flags & EVP_MD_CTX_FLAG_NO_INIT)
        return 1;
    return ctx->digest->init(ctx);
}