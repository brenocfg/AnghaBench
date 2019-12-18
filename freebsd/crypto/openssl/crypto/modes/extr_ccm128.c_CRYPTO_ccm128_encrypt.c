#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  (* block128_f ) (unsigned char*,unsigned char*,void*) ;
struct TYPE_6__ {unsigned char* c; } ;
struct TYPE_5__ {unsigned char* c; int* u; } ;
struct TYPE_7__ {int blocks; TYPE_2__ nonce; TYPE_1__ cmac; void* key; int /*<<< orphan*/  (* block ) (unsigned char*,unsigned char*,void*) ;} ;
typedef  TYPE_3__ CCM128_CONTEXT ;

/* Variables and functions */
 int U64 (int) ; 
 int /*<<< orphan*/  ctr64_inc (unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  stub1 (unsigned char*,unsigned char*,void*) ; 
 int /*<<< orphan*/  stub2 (unsigned char*,unsigned char*,void*) ; 
 int /*<<< orphan*/  stub3 (unsigned char*,unsigned char*,void*) ; 
 int /*<<< orphan*/  stub4 (unsigned char*,unsigned char*,void*) ; 
 int /*<<< orphan*/  stub5 (unsigned char*,unsigned char*,void*) ; 
 int /*<<< orphan*/  stub6 (unsigned char*,unsigned char*,void*) ; 

int CRYPTO_ccm128_encrypt(CCM128_CONTEXT *ctx,
                          const unsigned char *inp, unsigned char *out,
                          size_t len)
{
    size_t n;
    unsigned int i, L;
    unsigned char flags0 = ctx->nonce.c[0];
    block128_f block = ctx->block;
    void *key = ctx->key;
    union {
        u64 u[2];
        u8 c[16];
    } scratch;

    if (!(flags0 & 0x40))
        (*block) (ctx->nonce.c, ctx->cmac.c, key), ctx->blocks++;

    ctx->nonce.c[0] = L = flags0 & 7;
    for (n = 0, i = 15 - L; i < 15; ++i) {
        n |= ctx->nonce.c[i];
        ctx->nonce.c[i] = 0;
        n <<= 8;
    }
    n |= ctx->nonce.c[15];      /* reconstructed length */
    ctx->nonce.c[15] = 1;

    if (n != len)
        return -1;              /* length mismatch */

    ctx->blocks += ((len + 15) >> 3) | 1;
    if (ctx->blocks > (U64(1) << 61))
        return -2;              /* too much data */

    while (len >= 16) {
#if defined(STRICT_ALIGNMENT)
        union {
            u64 u[2];
            u8 c[16];
        } temp;

        memcpy(temp.c, inp, 16);
        ctx->cmac.u[0] ^= temp.u[0];
        ctx->cmac.u[1] ^= temp.u[1];
#else
        ctx->cmac.u[0] ^= ((u64 *)inp)[0];
        ctx->cmac.u[1] ^= ((u64 *)inp)[1];
#endif
        (*block) (ctx->cmac.c, ctx->cmac.c, key);
        (*block) (ctx->nonce.c, scratch.c, key);
        ctr64_inc(ctx->nonce.c);
#if defined(STRICT_ALIGNMENT)
        temp.u[0] ^= scratch.u[0];
        temp.u[1] ^= scratch.u[1];
        memcpy(out, temp.c, 16);
#else
        ((u64 *)out)[0] = scratch.u[0] ^ ((u64 *)inp)[0];
        ((u64 *)out)[1] = scratch.u[1] ^ ((u64 *)inp)[1];
#endif
        inp += 16;
        out += 16;
        len -= 16;
    }

    if (len) {
        for (i = 0; i < len; ++i)
            ctx->cmac.c[i] ^= inp[i];
        (*block) (ctx->cmac.c, ctx->cmac.c, key);
        (*block) (ctx->nonce.c, scratch.c, key);
        for (i = 0; i < len; ++i)
            out[i] = scratch.c[i] ^ inp[i];
    }

    for (i = 15 - L; i < 16; ++i)
        ctx->nonce.c[i] = 0;

    (*block) (ctx->nonce.c, scratch.c, key);
    ctx->cmac.u[0] ^= scratch.u[0];
    ctx->cmac.u[1] ^= scratch.u[1];

    ctx->nonce.c[0] = flags0;

    return 0;
}