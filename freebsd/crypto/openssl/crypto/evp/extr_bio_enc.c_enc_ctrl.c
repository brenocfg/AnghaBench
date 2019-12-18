#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ok; int finished; long buf_len; long buf_off; int /*<<< orphan*/ * cipher; scalar_t__ buf; int /*<<< orphan*/  cont; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  TYPE_1__ BIO_ENC_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
#define  BIO_CTRL_DUP 136 
#define  BIO_CTRL_EOF 135 
#define  BIO_CTRL_FLUSH 134 
#define  BIO_CTRL_PENDING 133 
#define  BIO_CTRL_RESET 132 
#define  BIO_CTRL_WPENDING 131 
#define  BIO_C_DO_STATE_MACHINE 130 
#define  BIO_C_GET_CIPHER_CTX 129 
#define  BIO_C_GET_CIPHER_STATUS 128 
 int /*<<< orphan*/  BIO_clear_retry_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_copy_next_retry (int /*<<< orphan*/ *) ; 
 long BIO_ctrl (int /*<<< orphan*/ *,int,long,void*) ; 
 TYPE_1__* BIO_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_init (int /*<<< orphan*/ *,int) ; 
 long EVP_CIPHER_CTX_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_encrypting (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 long EVP_CipherFinal_ex (int /*<<< orphan*/ *,unsigned char*,long*) ; 
 int /*<<< orphan*/  EVP_CipherInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int enc_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long enc_ctrl(BIO *b, int cmd, long num, void *ptr)
{
    BIO *dbio;
    BIO_ENC_CTX *ctx, *dctx;
    long ret = 1;
    int i;
    EVP_CIPHER_CTX **c_ctx;
    BIO *next;

    ctx = BIO_get_data(b);
    next = BIO_next(b);
    if (ctx == NULL)
        return 0;

    switch (cmd) {
    case BIO_CTRL_RESET:
        ctx->ok = 1;
        ctx->finished = 0;
        if (!EVP_CipherInit_ex(ctx->cipher, NULL, NULL, NULL, NULL,
                               EVP_CIPHER_CTX_encrypting(ctx->cipher)))
            return 0;
        ret = BIO_ctrl(next, cmd, num, ptr);
        break;
    case BIO_CTRL_EOF:         /* More to read */
        if (ctx->cont <= 0)
            ret = 1;
        else
            ret = BIO_ctrl(next, cmd, num, ptr);
        break;
    case BIO_CTRL_WPENDING:
        ret = ctx->buf_len - ctx->buf_off;
        if (ret <= 0)
            ret = BIO_ctrl(next, cmd, num, ptr);
        break;
    case BIO_CTRL_PENDING:     /* More to read in buffer */
        ret = ctx->buf_len - ctx->buf_off;
        if (ret <= 0)
            ret = BIO_ctrl(next, cmd, num, ptr);
        break;
    case BIO_CTRL_FLUSH:
        /* do a final write */
 again:
        while (ctx->buf_len != ctx->buf_off) {
            i = enc_write(b, NULL, 0);
            if (i < 0)
                return i;
        }

        if (!ctx->finished) {
            ctx->finished = 1;
            ctx->buf_off = 0;
            ret = EVP_CipherFinal_ex(ctx->cipher,
                                     (unsigned char *)ctx->buf,
                                     &(ctx->buf_len));
            ctx->ok = (int)ret;
            if (ret <= 0)
                break;

            /* push out the bytes */
            goto again;
        }

        /* Finally flush the underlying BIO */
        ret = BIO_ctrl(next, cmd, num, ptr);
        break;
    case BIO_C_GET_CIPHER_STATUS:
        ret = (long)ctx->ok;
        break;
    case BIO_C_DO_STATE_MACHINE:
        BIO_clear_retry_flags(b);
        ret = BIO_ctrl(next, cmd, num, ptr);
        BIO_copy_next_retry(b);
        break;
    case BIO_C_GET_CIPHER_CTX:
        c_ctx = (EVP_CIPHER_CTX **)ptr;
        *c_ctx = ctx->cipher;
        BIO_set_init(b, 1);
        break;
    case BIO_CTRL_DUP:
        dbio = (BIO *)ptr;
        dctx = BIO_get_data(dbio);
        dctx->cipher = EVP_CIPHER_CTX_new();
        if (dctx->cipher == NULL)
            return 0;
        ret = EVP_CIPHER_CTX_copy(dctx->cipher, ctx->cipher);
        if (ret)
            BIO_set_init(dbio, 1);
        break;
    default:
        ret = BIO_ctrl(next, cmd, num, ptr);
        break;
    }
    return ret;
}