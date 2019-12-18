#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_7__ {int* d; } ;
typedef  TYPE_1__ secp256k1_scalar ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY_CHECK (int) ; 
 int secp256k1_scalar_check_overflow (TYPE_1__*) ; 
 int /*<<< orphan*/  secp256k1_scalar_reduce (TYPE_1__*,int) ; 

__attribute__((used)) static int secp256k1_scalar_add(secp256k1_scalar *r, const secp256k1_scalar *a, const secp256k1_scalar *b) {
    int overflow;
    uint64_t t = (uint64_t)a->d[0] + b->d[0];
    r->d[0] = t & 0xFFFFFFFFULL; t >>= 32;
    t += (uint64_t)a->d[1] + b->d[1];
    r->d[1] = t & 0xFFFFFFFFULL; t >>= 32;
    t += (uint64_t)a->d[2] + b->d[2];
    r->d[2] = t & 0xFFFFFFFFULL; t >>= 32;
    t += (uint64_t)a->d[3] + b->d[3];
    r->d[3] = t & 0xFFFFFFFFULL; t >>= 32;
    t += (uint64_t)a->d[4] + b->d[4];
    r->d[4] = t & 0xFFFFFFFFULL; t >>= 32;
    t += (uint64_t)a->d[5] + b->d[5];
    r->d[5] = t & 0xFFFFFFFFULL; t >>= 32;
    t += (uint64_t)a->d[6] + b->d[6];
    r->d[6] = t & 0xFFFFFFFFULL; t >>= 32;
    t += (uint64_t)a->d[7] + b->d[7];
    r->d[7] = t & 0xFFFFFFFFULL; t >>= 32;
    overflow = t + secp256k1_scalar_check_overflow(r);
    VERIFY_CHECK(overflow == 0 || overflow == 1);
    secp256k1_scalar_reduce(r, overflow);
    return overflow;
}