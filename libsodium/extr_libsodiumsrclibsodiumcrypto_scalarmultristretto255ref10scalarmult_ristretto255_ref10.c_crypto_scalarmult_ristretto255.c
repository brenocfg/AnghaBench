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
 int /*<<< orphan*/  ge25519_scalarmult (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 scalar_t__ ristretto255_frombytes (int /*<<< orphan*/ *,unsigned char const*) ; 
 int /*<<< orphan*/  ristretto255_p3_tobytes (unsigned char*,int /*<<< orphan*/ *) ; 
 scalar_t__ sodium_is_zero (unsigned char*,int) ; 

int
crypto_scalarmult_ristretto255(unsigned char *q, const unsigned char *n,
                               const unsigned char *p)
{
    unsigned char *t = q;
    ge25519_p3     Q;
    ge25519_p3     P;
    unsigned int   i;

    if (ristretto255_frombytes(&P, p) != 0) {
        return -1;
    }
    for (i = 0; i < 32; ++i) {
        t[i] = n[i];
    }
    t[31] &= 127;
    ge25519_scalarmult(&Q, t, &P);
    ristretto255_p3_tobytes(q, &Q);
    if (sodium_is_zero(q, 32)) {
        return -1;
    }
    return 0;
}