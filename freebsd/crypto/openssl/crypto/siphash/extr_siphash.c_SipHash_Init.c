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
typedef  int uint64_t ;
struct TYPE_3__ {scalar_t__ hash_size; int crounds; int drounds; int v0; int v1; int v2; int v3; scalar_t__ total_inlen; scalar_t__ len; } ;
typedef  TYPE_1__ SIPHASH ;

/* Variables and functions */
 int SIPHASH_C_ROUNDS ; 
 int SIPHASH_D_ROUNDS ; 
 scalar_t__ SIPHASH_MAX_DIGEST_SIZE ; 
 int U8TO64_LE (unsigned char const*) ; 
 scalar_t__ siphash_adjust_hash_size (scalar_t__) ; 

int SipHash_Init(SIPHASH *ctx, const unsigned char *k, int crounds, int drounds)
{
    uint64_t k0 = U8TO64_LE(k);
    uint64_t k1 = U8TO64_LE(k + 8);

    /* If the hash size wasn't set, i.e. is zero */
    ctx->hash_size = siphash_adjust_hash_size(ctx->hash_size);

    if (drounds == 0)
        drounds = SIPHASH_D_ROUNDS;
    if (crounds == 0)
        crounds = SIPHASH_C_ROUNDS;

    ctx->crounds = crounds;
    ctx->drounds = drounds;

    ctx->len = 0;
    ctx->total_inlen = 0;

    ctx->v0 = 0x736f6d6570736575ULL ^ k0;
    ctx->v1 = 0x646f72616e646f6dULL ^ k1;
    ctx->v2 = 0x6c7967656e657261ULL ^ k0;
    ctx->v3 = 0x7465646279746573ULL ^ k1;

    if (ctx->hash_size == SIPHASH_MAX_DIGEST_SIZE)
        ctx->v1 ^= 0xee;

    return 1;
}