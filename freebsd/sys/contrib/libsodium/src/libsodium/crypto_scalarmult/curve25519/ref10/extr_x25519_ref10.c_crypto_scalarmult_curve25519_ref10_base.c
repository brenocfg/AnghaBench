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
struct TYPE_3__ {int /*<<< orphan*/  Z; int /*<<< orphan*/  Y; } ;
typedef  TYPE_1__ ge25519_p3 ;
typedef  int /*<<< orphan*/  fe25519 ;

/* Variables and functions */
 int /*<<< orphan*/  edwards_to_montgomery (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe25519_tobytes (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ge25519_scalarmult_base (TYPE_1__*,unsigned char*) ; 

__attribute__((used)) static int
crypto_scalarmult_curve25519_ref10_base(unsigned char *q,
                                        const unsigned char *n)
{
    unsigned char *t = q;
    ge25519_p3     A;
    fe25519        pk;
    unsigned int   i;

    for (i = 0; i < 32; i++) {
        t[i] = n[i];
    }
    t[0] &= 248;
    t[31] &= 127;
    t[31] |= 64;
    ge25519_scalarmult_base(&A, t);
    edwards_to_montgomery(pk, A.Y, A.Z);
    fe25519_tobytes(q, pk);

    return 0;
}