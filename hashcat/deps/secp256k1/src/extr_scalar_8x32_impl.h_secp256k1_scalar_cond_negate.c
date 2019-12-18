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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int* d; } ;
typedef  TYPE_1__ secp256k1_scalar ;

/* Variables and functions */
 int SECP256K1_N_0 ; 
 int SECP256K1_N_1 ; 
 int SECP256K1_N_2 ; 
 int SECP256K1_N_3 ; 
 int SECP256K1_N_4 ; 
 int SECP256K1_N_5 ; 
 int SECP256K1_N_6 ; 
 int SECP256K1_N_7 ; 
 scalar_t__ secp256k1_scalar_is_zero (TYPE_1__*) ; 

__attribute__((used)) static int secp256k1_scalar_cond_negate(secp256k1_scalar *r, int flag) {
    /* If we are flag = 0, mask = 00...00 and this is a no-op;
     * if we are flag = 1, mask = 11...11 and this is identical to secp256k1_scalar_negate */
    uint32_t mask = !flag - 1;
    uint32_t nonzero = 0xFFFFFFFFUL * (secp256k1_scalar_is_zero(r) == 0);
    uint64_t t = (uint64_t)(r->d[0] ^ mask) + ((SECP256K1_N_0 + 1) & mask);
    r->d[0] = t & nonzero; t >>= 32;
    t += (uint64_t)(r->d[1] ^ mask) + (SECP256K1_N_1 & mask);
    r->d[1] = t & nonzero; t >>= 32;
    t += (uint64_t)(r->d[2] ^ mask) + (SECP256K1_N_2 & mask);
    r->d[2] = t & nonzero; t >>= 32;
    t += (uint64_t)(r->d[3] ^ mask) + (SECP256K1_N_3 & mask);
    r->d[3] = t & nonzero; t >>= 32;
    t += (uint64_t)(r->d[4] ^ mask) + (SECP256K1_N_4 & mask);
    r->d[4] = t & nonzero; t >>= 32;
    t += (uint64_t)(r->d[5] ^ mask) + (SECP256K1_N_5 & mask);
    r->d[5] = t & nonzero; t >>= 32;
    t += (uint64_t)(r->d[6] ^ mask) + (SECP256K1_N_6 & mask);
    r->d[6] = t & nonzero; t >>= 32;
    t += (uint64_t)(r->d[7] ^ mask) + (SECP256K1_N_7 & mask);
    r->d[7] = t & nonzero;
    return 2 * (mask == 0) - 1;
}