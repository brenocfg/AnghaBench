#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct TYPE_13__ {int hi; int lo; } ;
typedef  TYPE_4__ u128 ;
typedef  int /*<<< orphan*/  bitlen ;
struct TYPE_12__ {int* u; int /*<<< orphan*/  c; } ;
struct TYPE_11__ {int* u; } ;
struct TYPE_10__ {int* u; int /*<<< orphan*/ * c; } ;
struct TYPE_14__ {void (* gmult ) (int*,u128 const*) ;void (* ghash ) (int*,u128 const*,u8 const*,size_t) ;unsigned int mres; TYPE_3__ Xi; TYPE_2__ EK0; scalar_t__ Xn; TYPE_1__ len; scalar_t__ ares; } ;
typedef  TYPE_5__ GCM128_CONTEXT ;

/* Variables and functions */
 int BSWAP8 (int) ; 
 int CRYPTO_memcmp (int /*<<< orphan*/ ,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  GCM_MUL (TYPE_5__*) ; 
 int GETU32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GHASH (TYPE_5__*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,TYPE_4__*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 

int CRYPTO_gcm128_finish(GCM128_CONTEXT *ctx, const unsigned char *tag,
                         size_t len)
{
    const union {
        long one;
        char little;
    } is_endian = { 1 };
    u64 alen = ctx->len.u[0] << 3;
    u64 clen = ctx->len.u[1] << 3;
#ifdef GCM_FUNCREF_4BIT
    void (*gcm_gmult_p) (u64 Xi[2], const u128 Htable[16]) = ctx->gmult;
# if defined(GHASH) && !defined(OPENSSL_SMALL_FOOTPRINT)
    void (*gcm_ghash_p) (u64 Xi[2], const u128 Htable[16],
                         const u8 *inp, size_t len) = ctx->ghash;
# endif
#endif

#if defined(GHASH) && !defined(OPENSSL_SMALL_FOOTPRINT)
    u128 bitlen;
    unsigned int mres = ctx->mres;

    if (mres) {
        unsigned blocks = (mres + 15) & -16;

        memset(ctx->Xn + mres, 0, blocks - mres);
        mres = blocks;
        if (mres == sizeof(ctx->Xn)) {
            GHASH(ctx, ctx->Xn, mres);
            mres = 0;
        }
    } else if (ctx->ares) {
        GCM_MUL(ctx);
    }
#else
    if (ctx->mres || ctx->ares)
        GCM_MUL(ctx);
#endif

    if (is_endian.little) {
#ifdef BSWAP8
        alen = BSWAP8(alen);
        clen = BSWAP8(clen);
#else
        u8 *p = ctx->len.c;

        ctx->len.u[0] = alen;
        ctx->len.u[1] = clen;

        alen = (u64)GETU32(p) << 32 | GETU32(p + 4);
        clen = (u64)GETU32(p + 8) << 32 | GETU32(p + 12);
#endif
    }

#if defined(GHASH) && !defined(OPENSSL_SMALL_FOOTPRINT)
    bitlen.hi = alen;
    bitlen.lo = clen;
    memcpy(ctx->Xn + mres, &bitlen, sizeof(bitlen));
    mres += sizeof(bitlen);
    GHASH(ctx, ctx->Xn, mres);
#else
    ctx->Xi.u[0] ^= alen;
    ctx->Xi.u[1] ^= clen;
    GCM_MUL(ctx);
#endif

    ctx->Xi.u[0] ^= ctx->EK0.u[0];
    ctx->Xi.u[1] ^= ctx->EK0.u[1];

    if (tag && len <= sizeof(ctx->Xi))
        return CRYPTO_memcmp(ctx->Xi.c, tag, len);
    else
        return -1;
}