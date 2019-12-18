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
struct TYPE_3__ {scalar_t__* h; } ;
typedef  scalar_t__ SHA_LONG64 ;
typedef  TYPE_1__ SHA512_CTX ;

/* Variables and functions */
 scalar_t__ PULL64 (scalar_t__ const) ; 
 int /*<<< orphan*/  ROUND_00_15 (int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ROUND_16_80 (int,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  SHA_LBLOCK ; 

__attribute__((used)) static void sha512_block_data_order(SHA512_CTX *ctx, const void *in,
                                    size_t num)
{
    const SHA_LONG64 *W = in;
    SHA_LONG64 a, b, c, d, e, f, g, h, s0, s1, T1;
    SHA_LONG64 X[16];
    int i;

    while (num--) {

        a = ctx->h[0];
        b = ctx->h[1];
        c = ctx->h[2];
        d = ctx->h[3];
        e = ctx->h[4];
        f = ctx->h[5];
        g = ctx->h[6];
        h = ctx->h[7];

#  ifdef B_ENDIAN
        T1 = X[0] = W[0];
        ROUND_00_15(0, a, b, c, d, e, f, g, h);
        T1 = X[1] = W[1];
        ROUND_00_15(1, h, a, b, c, d, e, f, g);
        T1 = X[2] = W[2];
        ROUND_00_15(2, g, h, a, b, c, d, e, f);
        T1 = X[3] = W[3];
        ROUND_00_15(3, f, g, h, a, b, c, d, e);
        T1 = X[4] = W[4];
        ROUND_00_15(4, e, f, g, h, a, b, c, d);
        T1 = X[5] = W[5];
        ROUND_00_15(5, d, e, f, g, h, a, b, c);
        T1 = X[6] = W[6];
        ROUND_00_15(6, c, d, e, f, g, h, a, b);
        T1 = X[7] = W[7];
        ROUND_00_15(7, b, c, d, e, f, g, h, a);
        T1 = X[8] = W[8];
        ROUND_00_15(8, a, b, c, d, e, f, g, h);
        T1 = X[9] = W[9];
        ROUND_00_15(9, h, a, b, c, d, e, f, g);
        T1 = X[10] = W[10];
        ROUND_00_15(10, g, h, a, b, c, d, e, f);
        T1 = X[11] = W[11];
        ROUND_00_15(11, f, g, h, a, b, c, d, e);
        T1 = X[12] = W[12];
        ROUND_00_15(12, e, f, g, h, a, b, c, d);
        T1 = X[13] = W[13];
        ROUND_00_15(13, d, e, f, g, h, a, b, c);
        T1 = X[14] = W[14];
        ROUND_00_15(14, c, d, e, f, g, h, a, b);
        T1 = X[15] = W[15];
        ROUND_00_15(15, b, c, d, e, f, g, h, a);
#  else
        T1 = X[0] = PULL64(W[0]);
        ROUND_00_15(0, a, b, c, d, e, f, g, h);
        T1 = X[1] = PULL64(W[1]);
        ROUND_00_15(1, h, a, b, c, d, e, f, g);
        T1 = X[2] = PULL64(W[2]);
        ROUND_00_15(2, g, h, a, b, c, d, e, f);
        T1 = X[3] = PULL64(W[3]);
        ROUND_00_15(3, f, g, h, a, b, c, d, e);
        T1 = X[4] = PULL64(W[4]);
        ROUND_00_15(4, e, f, g, h, a, b, c, d);
        T1 = X[5] = PULL64(W[5]);
        ROUND_00_15(5, d, e, f, g, h, a, b, c);
        T1 = X[6] = PULL64(W[6]);
        ROUND_00_15(6, c, d, e, f, g, h, a, b);
        T1 = X[7] = PULL64(W[7]);
        ROUND_00_15(7, b, c, d, e, f, g, h, a);
        T1 = X[8] = PULL64(W[8]);
        ROUND_00_15(8, a, b, c, d, e, f, g, h);
        T1 = X[9] = PULL64(W[9]);
        ROUND_00_15(9, h, a, b, c, d, e, f, g);
        T1 = X[10] = PULL64(W[10]);
        ROUND_00_15(10, g, h, a, b, c, d, e, f);
        T1 = X[11] = PULL64(W[11]);
        ROUND_00_15(11, f, g, h, a, b, c, d, e);
        T1 = X[12] = PULL64(W[12]);
        ROUND_00_15(12, e, f, g, h, a, b, c, d);
        T1 = X[13] = PULL64(W[13]);
        ROUND_00_15(13, d, e, f, g, h, a, b, c);
        T1 = X[14] = PULL64(W[14]);
        ROUND_00_15(14, c, d, e, f, g, h, a, b);
        T1 = X[15] = PULL64(W[15]);
        ROUND_00_15(15, b, c, d, e, f, g, h, a);
#  endif

        for (i = 16; i < 80; i += 16) {
            ROUND_16_80(i, 0, a, b, c, d, e, f, g, h, X);
            ROUND_16_80(i, 1, h, a, b, c, d, e, f, g, X);
            ROUND_16_80(i, 2, g, h, a, b, c, d, e, f, X);
            ROUND_16_80(i, 3, f, g, h, a, b, c, d, e, X);
            ROUND_16_80(i, 4, e, f, g, h, a, b, c, d, X);
            ROUND_16_80(i, 5, d, e, f, g, h, a, b, c, X);
            ROUND_16_80(i, 6, c, d, e, f, g, h, a, b, X);
            ROUND_16_80(i, 7, b, c, d, e, f, g, h, a, X);
            ROUND_16_80(i, 8, a, b, c, d, e, f, g, h, X);
            ROUND_16_80(i, 9, h, a, b, c, d, e, f, g, X);
            ROUND_16_80(i, 10, g, h, a, b, c, d, e, f, X);
            ROUND_16_80(i, 11, f, g, h, a, b, c, d, e, X);
            ROUND_16_80(i, 12, e, f, g, h, a, b, c, d, X);
            ROUND_16_80(i, 13, d, e, f, g, h, a, b, c, X);
            ROUND_16_80(i, 14, c, d, e, f, g, h, a, b, X);
            ROUND_16_80(i, 15, b, c, d, e, f, g, h, a, X);
        }

        ctx->h[0] += a;
        ctx->h[1] += b;
        ctx->h[2] += c;
        ctx->h[3] += d;
        ctx->h[4] += e;
        ctx->h[5] += f;
        ctx->h[6] += g;
        ctx->h[7] += h;

        W += SHA_LBLOCK;
    }
}