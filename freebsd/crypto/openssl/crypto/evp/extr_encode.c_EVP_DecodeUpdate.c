#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num; unsigned char* enc_data; int flags; } ;
typedef  TYPE_1__ EVP_ENCODE_CTX ;

/* Variables and functions */
 scalar_t__ B64_BASE64 (int) ; 
 int B64_EOF ; 
 int B64_ERROR ; 
 int EVP_ENCODE_CTX_USE_SRP_ALPHABET ; 
 int /*<<< orphan*/  OPENSSL_assert (int) ; 
 int conv_ascii2bin (int,unsigned char const*) ; 
 unsigned char* data_ascii2bin ; 
 int evp_decodeblock_int (TYPE_1__*,unsigned char*,unsigned char*,int) ; 
 unsigned char* srpdata_ascii2bin ; 

int EVP_DecodeUpdate(EVP_ENCODE_CTX *ctx, unsigned char *out, int *outl,
                     const unsigned char *in, int inl)
{
    int seof = 0, eof = 0, rv = -1, ret = 0, i, v, tmp, n, decoded_len;
    unsigned char *d;
    const unsigned char *table;

    n = ctx->num;
    d = ctx->enc_data;

    if (n > 0 && d[n - 1] == '=') {
        eof++;
        if (n > 1 && d[n - 2] == '=')
            eof++;
    }

     /* Legacy behaviour: an empty input chunk signals end of input. */
    if (inl == 0) {
        rv = 0;
        goto end;
    }

    if ((ctx->flags & EVP_ENCODE_CTX_USE_SRP_ALPHABET) != 0)
        table = srpdata_ascii2bin;
    else
        table = data_ascii2bin;

    for (i = 0; i < inl; i++) {
        tmp = *(in++);
        v = conv_ascii2bin(tmp, table);
        if (v == B64_ERROR) {
            rv = -1;
            goto end;
        }

        if (tmp == '=') {
            eof++;
        } else if (eof > 0 && B64_BASE64(v)) {
            /* More data after padding. */
            rv = -1;
            goto end;
        }

        if (eof > 2) {
            rv = -1;
            goto end;
        }

        if (v == B64_EOF) {
            seof = 1;
            goto tail;
        }

        /* Only save valid base64 characters. */
        if (B64_BASE64(v)) {
            if (n >= 64) {
                /*
                 * We increment n once per loop, and empty the buffer as soon as
                 * we reach 64 characters, so this can only happen if someone's
                 * manually messed with the ctx. Refuse to write any more data.
                 */
                rv = -1;
                goto end;
            }
            OPENSSL_assert(n < (int)sizeof(ctx->enc_data));
            d[n++] = tmp;
        }

        if (n == 64) {
            decoded_len = evp_decodeblock_int(ctx, out, d, n);
            n = 0;
            if (decoded_len < 0 || eof > decoded_len) {
                rv = -1;
                goto end;
            }
            ret += decoded_len - eof;
            out += decoded_len - eof;
        }
    }

    /*
     * Legacy behaviour: if the current line is a full base64-block (i.e., has
     * 0 mod 4 base64 characters), it is processed immediately. We keep this
     * behaviour as applications may not be calling EVP_DecodeFinal properly.
     */
tail:
    if (n > 0) {
        if ((n & 3) == 0) {
            decoded_len = evp_decodeblock_int(ctx, out, d, n);
            n = 0;
            if (decoded_len < 0 || eof > decoded_len) {
                rv = -1;
                goto end;
            }
            ret += (decoded_len - eof);
        } else if (seof) {
            /* EOF in the middle of a base64 block. */
            rv = -1;
            goto end;
        }
    }

    rv = seof || (n == 0 && eof) ? 0 : 1;
end:
    /* Legacy behaviour. This should probably rather be zeroed on error. */
    *outl = ret;
    ctx->num = n;
    return rv;
}