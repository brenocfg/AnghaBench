#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ encode; int buf_len; int buf_off; size_t tmp_len; int cont; unsigned char* tmp; int tmp_nl; int /*<<< orphan*/ * buf; int /*<<< orphan*/  base64; scalar_t__ start; } ;
typedef  TYPE_1__ BIO_B64_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int B64_BLOCK_SIZE ; 
 scalar_t__ B64_DECODE ; 
 int BIO_FLAGS_BASE64_NO_NL ; 
 int /*<<< orphan*/  BIO_clear_retry_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_copy_next_retry (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_get_data (int /*<<< orphan*/ *) ; 
 int BIO_get_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_next (int /*<<< orphan*/ *) ; 
 int BIO_read (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  BIO_should_retry (int /*<<< orphan*/ *) ; 
 int EVP_DecodeBlock (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  EVP_DecodeInit (int /*<<< orphan*/ ) ; 
 int EVP_DecodeUpdate (int /*<<< orphan*/ ,unsigned char*,int*,unsigned char*,int) ; 
 int /*<<< orphan*/  OPENSSL_assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 

__attribute__((used)) static int b64_read(BIO *b, char *out, int outl)
{
    int ret = 0, i, ii, j, k, x, n, num, ret_code = 0;
    BIO_B64_CTX *ctx;
    unsigned char *p, *q;
    BIO *next;

    if (out == NULL)
        return 0;
    ctx = (BIO_B64_CTX *)BIO_get_data(b);

    next = BIO_next(b);
    if ((ctx == NULL) || (next == NULL))
        return 0;

    BIO_clear_retry_flags(b);

    if (ctx->encode != B64_DECODE) {
        ctx->encode = B64_DECODE;
        ctx->buf_len = 0;
        ctx->buf_off = 0;
        ctx->tmp_len = 0;
        EVP_DecodeInit(ctx->base64);
    }

    /* First check if there are bytes decoded/encoded */
    if (ctx->buf_len > 0) {
        OPENSSL_assert(ctx->buf_len >= ctx->buf_off);
        i = ctx->buf_len - ctx->buf_off;
        if (i > outl)
            i = outl;
        OPENSSL_assert(ctx->buf_off + i < (int)sizeof(ctx->buf));
        memcpy(out, &(ctx->buf[ctx->buf_off]), i);
        ret = i;
        out += i;
        outl -= i;
        ctx->buf_off += i;
        if (ctx->buf_len == ctx->buf_off) {
            ctx->buf_len = 0;
            ctx->buf_off = 0;
        }
    }

    /*
     * At this point, we have room of outl bytes and an empty buffer, so we
     * should read in some more.
     */

    ret_code = 0;
    while (outl > 0) {
        if (ctx->cont <= 0)
            break;

        i = BIO_read(next, &(ctx->tmp[ctx->tmp_len]),
                     B64_BLOCK_SIZE - ctx->tmp_len);

        if (i <= 0) {
            ret_code = i;

            /* Should we continue next time we are called? */
            if (!BIO_should_retry(next)) {
                ctx->cont = i;
                /* If buffer empty break */
                if (ctx->tmp_len == 0)
                    break;
                /* Fall through and process what we have */
                else
                    i = 0;
            }
            /* else we retry and add more data to buffer */
            else
                break;
        }
        i += ctx->tmp_len;
        ctx->tmp_len = i;

        /*
         * We need to scan, a line at a time until we have a valid line if we
         * are starting.
         */
        if (ctx->start && (BIO_get_flags(b) & BIO_FLAGS_BASE64_NO_NL)) {
            /* ctx->start=1; */
            ctx->tmp_len = 0;
        } else if (ctx->start) {
            q = p = (unsigned char *)ctx->tmp;
            num = 0;
            for (j = 0; j < i; j++) {
                if (*(q++) != '\n')
                    continue;

                /*
                 * due to a previous very long line, we need to keep on
                 * scanning for a '\n' before we even start looking for
                 * base64 encoded stuff.
                 */
                if (ctx->tmp_nl) {
                    p = q;
                    ctx->tmp_nl = 0;
                    continue;
                }

                k = EVP_DecodeUpdate(ctx->base64,
                                     (unsigned char *)ctx->buf,
                                     &num, p, q - p);
                if ((k <= 0) && (num == 0) && (ctx->start))
                    EVP_DecodeInit(ctx->base64);
                else {
                    if (p != (unsigned char *)
                        &(ctx->tmp[0])) {
                        i -= (p - (unsigned char *)
                              &(ctx->tmp[0]));
                        for (x = 0; x < i; x++)
                            ctx->tmp[x] = p[x];
                    }
                    EVP_DecodeInit(ctx->base64);
                    ctx->start = 0;
                    break;
                }
                p = q;
            }

            /* we fell off the end without starting */
            if ((j == i) && (num == 0)) {
                /*
                 * Is this is one long chunk?, if so, keep on reading until a
                 * new line.
                 */
                if (p == (unsigned char *)&(ctx->tmp[0])) {
                    /* Check buffer full */
                    if (i == B64_BLOCK_SIZE) {
                        ctx->tmp_nl = 1;
                        ctx->tmp_len = 0;
                    }
                } else if (p != q) { /* finished on a '\n' */
                    n = q - p;
                    for (ii = 0; ii < n; ii++)
                        ctx->tmp[ii] = p[ii];
                    ctx->tmp_len = n;
                }
                /* else finished on a '\n' */
                continue;
            } else {
                ctx->tmp_len = 0;
            }
        } else if ((i < B64_BLOCK_SIZE) && (ctx->cont > 0)) {
            /*
             * If buffer isn't full and we can retry then restart to read in
             * more data.
             */
            continue;
        }

        if (BIO_get_flags(b) & BIO_FLAGS_BASE64_NO_NL) {
            int z, jj;

            jj = i & ~3;        /* process per 4 */
            z = EVP_DecodeBlock((unsigned char *)ctx->buf,
                                (unsigned char *)ctx->tmp, jj);
            if (jj > 2) {
                if (ctx->tmp[jj - 1] == '=') {
                    z--;
                    if (ctx->tmp[jj - 2] == '=')
                        z--;
                }
            }
            /*
             * z is now number of output bytes and jj is the number consumed
             */
            if (jj != i) {
                memmove(ctx->tmp, &ctx->tmp[jj], i - jj);
                ctx->tmp_len = i - jj;
            }
            ctx->buf_len = 0;
            if (z > 0) {
                ctx->buf_len = z;
            }
            i = z;
        } else {
            i = EVP_DecodeUpdate(ctx->base64,
                                 (unsigned char *)ctx->buf, &ctx->buf_len,
                                 (unsigned char *)ctx->tmp, i);
            ctx->tmp_len = 0;
        }
        /*
         * If eof or an error was signalled, then the condition
         * 'ctx->cont <= 0' will prevent b64_read() from reading
         * more data on subsequent calls. This assignment was
         * deleted accidentally in commit 5562cfaca4f3.
         */
        ctx->cont = i;

        ctx->buf_off = 0;
        if (i < 0) {
            ret_code = 0;
            ctx->buf_len = 0;
            break;
        }

        if (ctx->buf_len <= outl)
            i = ctx->buf_len;
        else
            i = outl;

        memcpy(out, ctx->buf, i);
        ret += i;
        ctx->buf_off = i;
        if (ctx->buf_off == ctx->buf_len) {
            ctx->buf_len = 0;
            ctx->buf_off = 0;
        }
        outl -= i;
        out += i;
    }
    /* BIO_clear_retry_flags(b); */
    BIO_copy_next_retry(b);
    return ((ret == 0) ? ret_code : ret);
}