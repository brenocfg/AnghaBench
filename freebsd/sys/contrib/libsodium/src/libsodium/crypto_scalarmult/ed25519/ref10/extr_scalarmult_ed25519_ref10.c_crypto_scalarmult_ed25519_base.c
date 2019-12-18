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
 int /*<<< orphan*/  _crypto_scalarmult_ed25519_clamp (unsigned char*) ; 
 int /*<<< orphan*/  ge25519_p3_tobytes (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_scalarmult_base (int /*<<< orphan*/ *,unsigned char*) ; 
 scalar_t__ sodium_is_zero (unsigned char const*,int) ; 

int
crypto_scalarmult_ed25519_base(unsigned char *q,
                               const unsigned char *n)
{
    unsigned char *t = q;
    ge25519_p3     Q;
    unsigned int   i;

    for (i = 0; i < 32; ++i) {
        t[i] = n[i];
    }
    _crypto_scalarmult_ed25519_clamp(t);
    ge25519_scalarmult_base(&Q, t);
    ge25519_p3_tobytes(q, &Q);
    if (sodium_is_zero(n, 32) != 0) {
        return -1;
    }
    return 0;
}