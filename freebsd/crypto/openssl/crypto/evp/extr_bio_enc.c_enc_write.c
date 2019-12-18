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
struct TYPE_3__ {int buf_len; int buf_off; int /*<<< orphan*/ * buf; scalar_t__ ok; int /*<<< orphan*/  cipher; } ;
typedef  TYPE_1__ BIO_ENC_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_clear_retry_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_copy_next_retry (int /*<<< orphan*/ *) ; 
 TYPE_1__* BIO_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_next (int /*<<< orphan*/ *) ; 
 int BIO_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int ENC_BLOCK_SIZE ; 
 int /*<<< orphan*/  EVP_CipherUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,unsigned char const*,int) ; 

__attribute__((used)) static int enc_write(BIO *b, const char *in, int inl)
{
    int ret = 0, n, i;
    BIO_ENC_CTX *ctx;
    BIO *next;

    ctx = BIO_get_data(b);
    next = BIO_next(b);
    if ((ctx == NULL) || (next == NULL))
        return 0;

    ret = inl;

    BIO_clear_retry_flags(b);
    n = ctx->buf_len - ctx->buf_off;
    while (n > 0) {
        i = BIO_write(next, &(ctx->buf[ctx->buf_off]), n);
        if (i <= 0) {
            BIO_copy_next_retry(b);
            return i;
        }
        ctx->buf_off += i;
        n -= i;
    }
    /* at this point all pending data has been written */

    if ((in == NULL) || (inl <= 0))
        return 0;

    ctx->buf_off = 0;
    while (inl > 0) {
        n = (inl > ENC_BLOCK_SIZE) ? ENC_BLOCK_SIZE : inl;
        if (!EVP_CipherUpdate(ctx->cipher,
                              ctx->buf, &ctx->buf_len,
                              (const unsigned char *)in, n)) {
            BIO_clear_retry_flags(b);
            ctx->ok = 0;
            return 0;
        }
        inl -= n;
        in += n;

        ctx->buf_off = 0;
        n = ctx->buf_len;
        while (n > 0) {
            i = BIO_write(next, &(ctx->buf[ctx->buf_off]), n);
            if (i <= 0) {
                BIO_copy_next_retry(b);
                return (ret == inl) ? i : ret - inl;
            }
            n -= i;
            ctx->buf_off += i;
        }
        ctx->buf_len = 0;
        ctx->buf_off = 0;
    }
    BIO_copy_next_retry(b);
    return ret;
}