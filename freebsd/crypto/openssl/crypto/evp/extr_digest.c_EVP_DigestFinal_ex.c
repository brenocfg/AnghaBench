#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* digest; int /*<<< orphan*/  md_data; } ;
struct TYPE_7__ {unsigned int md_size; int (* final ) (TYPE_2__*,unsigned char*) ;int /*<<< orphan*/  ctx_size; int /*<<< orphan*/  (* cleanup ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ EVP_MD_CTX ;

/* Variables and functions */
 unsigned int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_MD_CTX_FLAG_CLEANED ; 
 int /*<<< orphan*/  EVP_MD_CTX_set_flags (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_assert (int) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,unsigned char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

int EVP_DigestFinal_ex(EVP_MD_CTX *ctx, unsigned char *md, unsigned int *size)
{
    int ret;

    OPENSSL_assert(ctx->digest->md_size <= EVP_MAX_MD_SIZE);
    ret = ctx->digest->final(ctx, md);
    if (size != NULL)
        *size = ctx->digest->md_size;
    if (ctx->digest->cleanup) {
        ctx->digest->cleanup(ctx);
        EVP_MD_CTX_set_flags(ctx, EVP_MD_CTX_FLAG_CLEANED);
    }
    OPENSSL_cleanse(ctx->md_data, ctx->digest->ctx_size);
    return ret;
}