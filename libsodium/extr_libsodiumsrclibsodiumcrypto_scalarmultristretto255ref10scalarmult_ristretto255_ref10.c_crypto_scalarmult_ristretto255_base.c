#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ge25519_p3 ;

/* Variables and functions */
 int /*<<< orphan*/  ge25519_scalarmult_base (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  ristretto255_p3_tobytes (unsigned char*,int /*<<< orphan*/ *) ; 
 scalar_t__ sodium_is_zero (unsigned char*,int) ; 

int
crypto_scalarmult_ristretto255_base(unsigned char *q,
                                    const unsigned char *n)
{
    unsigned char *t = q;
    ge25519_p3     Q;
    unsigned int   i;

    for (i = 0; i < 32; ++i) {
        t[i] = n[i];
    }
    t[31] &= 127;
    ge25519_scalarmult_base(&Q, t);
    ristretto255_p3_tobytes(q, &Q);
    if (sodium_is_zero(q, 32)) {
        return -1;
    }
    return 0;
}