#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* digest; int /*<<< orphan*/  md_data; } ;
struct TYPE_8__ {int flags; int (* final ) (TYPE_2__*,unsigned char*) ;int /*<<< orphan*/  ctx_size; int /*<<< orphan*/  (* cleanup ) (TYPE_2__*) ;scalar_t__ (* md_ctrl ) (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_F_EVP_DIGESTFINALXOF ; 
 int /*<<< orphan*/  EVP_MD_CTRL_XOF_LEN ; 
 int /*<<< orphan*/  EVP_MD_CTX_FLAG_CLEANED ; 
 int /*<<< orphan*/  EVP_MD_CTX_set_flags (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int EVP_MD_FLAG_XOF ; 
 int /*<<< orphan*/  EVP_R_NOT_XOF_OR_INVALID_LENGTH ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t INT_MAX ; 
 int /*<<< orphan*/  OPENSSL_cleanse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int stub2 (TYPE_2__*,unsigned char*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*) ; 

int EVP_DigestFinalXOF(EVP_MD_CTX *ctx, unsigned char *md, size_t size)
{
    int ret = 0;

    if (ctx->digest->flags & EVP_MD_FLAG_XOF
        && size <= INT_MAX
        && ctx->digest->md_ctrl(ctx, EVP_MD_CTRL_XOF_LEN, (int)size, NULL)) {
        ret = ctx->digest->final(ctx, md);

        if (ctx->digest->cleanup != NULL) {
            ctx->digest->cleanup(ctx);
            EVP_MD_CTX_set_flags(ctx, EVP_MD_CTX_FLAG_CLEANED);
        }
        OPENSSL_cleanse(ctx->md_data, ctx->digest->ctx_size);
    } else {
        EVPerr(EVP_F_EVP_DIGESTFINALXOF, EVP_R_NOT_XOF_OR_INVALID_LENGTH);
    }

    return ret;
}