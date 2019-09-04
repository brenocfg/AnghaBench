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
typedef  int uint32_t ;
struct TYPE_3__ {int* state; } ;
typedef  TYPE_1__ _picohash_sha256_ctx_t ;

/* Variables and functions */
 int _picohash_sha256_gamma0 (int) ; 
 int _picohash_sha256_gamma1 (int) ; 
 int /*<<< orphan*/  _picohash_sha256_rnd (int,int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static inline void _picohash_sha256_compress(_picohash_sha256_ctx_t *ctx, unsigned char *buf)
{
    static const uint32_t K[64] = {
        0x428a2f98UL, 0x71374491UL, 0xb5c0fbcfUL, 0xe9b5dba5UL, 0x3956c25bUL, 0x59f111f1UL, 0x923f82a4UL, 0xab1c5ed5UL,
        0xd807aa98UL, 0x12835b01UL, 0x243185beUL, 0x550c7dc3UL, 0x72be5d74UL, 0x80deb1feUL, 0x9bdc06a7UL, 0xc19bf174UL,
        0xe49b69c1UL, 0xefbe4786UL, 0x0fc19dc6UL, 0x240ca1ccUL, 0x2de92c6fUL, 0x4a7484aaUL, 0x5cb0a9dcUL, 0x76f988daUL,
        0x983e5152UL, 0xa831c66dUL, 0xb00327c8UL, 0xbf597fc7UL, 0xc6e00bf3UL, 0xd5a79147UL, 0x06ca6351UL, 0x14292967UL,
        0x27b70a85UL, 0x2e1b2138UL, 0x4d2c6dfcUL, 0x53380d13UL, 0x650a7354UL, 0x766a0abbUL, 0x81c2c92eUL, 0x92722c85UL,
        0xa2bfe8a1UL, 0xa81a664bUL, 0xc24b8b70UL, 0xc76c51a3UL, 0xd192e819UL, 0xd6990624UL, 0xf40e3585UL, 0x106aa070UL,
        0x19a4c116UL, 0x1e376c08UL, 0x2748774cUL, 0x34b0bcb5UL, 0x391c0cb3UL, 0x4ed8aa4aUL, 0x5b9cca4fUL, 0x682e6ff3UL,
        0x748f82eeUL, 0x78a5636fUL, 0x84c87814UL, 0x8cc70208UL, 0x90befffaUL, 0xa4506cebUL, 0xbef9a3f7UL, 0xc67178f2UL};
    uint32_t S[8], W[64], t, t0, t1;
    int i;

    /* copy state into S */
    for (i = 0; i < 8; i++)
        S[i] = ctx->state[i];

    /* copy the state into 512-bits into W[0..15] */
    for (i = 0; i < 16; i++)
        W[i] =
            (uint32_t)buf[4 * i] << 24 | (uint32_t)buf[4 * i + 1] << 16 | (uint32_t)buf[4 * i + 2] << 8 | (uint32_t)buf[4 * i + 3];

    /* fill W[16..63] */
    for (i = 16; i < 64; i++)
        W[i] = _picohash_sha256_gamma1(W[i - 2]) + W[i - 7] + _picohash_sha256_gamma0(W[i - 15]) + W[i - 16];

    /* Compress */
    for (i = 0; i < 64; ++i) {
        _picohash_sha256_rnd(S[0], S[1], S[2], S[3], S[4], S[5], S[6], S[7], i);
        t = S[7];
        S[7] = S[6];
        S[6] = S[5];
        S[5] = S[4];
        S[4] = S[3];
        S[3] = S[2];
        S[2] = S[1];
        S[1] = S[0];
        S[0] = t;
    }

    /* feedback */
    for (i = 0; i < 8; i++)
        ctx->state[i] = ctx->state[i] + S[i];
}