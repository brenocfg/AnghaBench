#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * digest; } ;
typedef  TYPE_1__ EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
#define  BIO_CTRL_DUP 134 
#define  BIO_CTRL_RESET 133 
#define  BIO_C_DO_STATE_MACHINE 132 
#define  BIO_C_GET_MD 131 
#define  BIO_C_GET_MD_CTX 130 
#define  BIO_C_SET_MD 129 
#define  BIO_C_SET_MD_CTX 128 
 int /*<<< orphan*/  BIO_clear_retry_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_copy_next_retry (int /*<<< orphan*/ *) ; 
 long BIO_ctrl (int /*<<< orphan*/ *,int,long,void*) ; 
 TYPE_1__* BIO_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_get_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_data (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  BIO_set_init (int /*<<< orphan*/ *,int) ; 
 long EVP_DigestInit_ex (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_CTX_copy_ex (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static long md_ctrl(BIO *b, int cmd, long num, void *ptr)
{
    EVP_MD_CTX *ctx, *dctx, **pctx;
    const EVP_MD **ppmd;
    EVP_MD *md;
    long ret = 1;
    BIO *dbio, *next;


    ctx = BIO_get_data(b);
    next = BIO_next(b);

    switch (cmd) {
    case BIO_CTRL_RESET:
        if (BIO_get_init(b))
            ret = EVP_DigestInit_ex(ctx, ctx->digest, NULL);
        else
            ret = 0;
        if (ret > 0)
            ret = BIO_ctrl(next, cmd, num, ptr);
        break;
    case BIO_C_GET_MD:
        if (BIO_get_init(b)) {
            ppmd = ptr;
            *ppmd = ctx->digest;
        } else
            ret = 0;
        break;
    case BIO_C_GET_MD_CTX:
        pctx = ptr;
        *pctx = ctx;
        BIO_set_init(b, 1);
        break;
    case BIO_C_SET_MD_CTX:
        if (BIO_get_init(b))
            BIO_set_data(b, ptr);
        else
            ret = 0;
        break;
    case BIO_C_DO_STATE_MACHINE:
        BIO_clear_retry_flags(b);
        ret = BIO_ctrl(next, cmd, num, ptr);
        BIO_copy_next_retry(b);
        break;

    case BIO_C_SET_MD:
        md = ptr;
        ret = EVP_DigestInit_ex(ctx, md, NULL);
        if (ret > 0)
            BIO_set_init(b, 1);
        break;
    case BIO_CTRL_DUP:
        dbio = ptr;
        dctx = BIO_get_data(dbio);
        if (!EVP_MD_CTX_copy_ex(dctx, ctx))
            return 0;
        BIO_set_init(b, 1);
        break;
    default:
        ret = BIO_ctrl(next, cmd, num, ptr);
        break;
    }
    return ret;
}