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

/* Variables and functions */
 int /*<<< orphan*/  sc25519_mul (unsigned char*,unsigned char*,unsigned char const*) ; 
 int /*<<< orphan*/  sc25519_sq (unsigned char*,unsigned char const*) ; 
 int /*<<< orphan*/  sc25519_sqmul (unsigned char*,int,unsigned char*) ; 

void
sc25519_invert(unsigned char recip[32], const unsigned char s[32])
{
    unsigned char _10[32], _100[32], _11[32], _101[32], _111[32],
        _1001[32], _1011[32], _1111[32];

    sc25519_sq(_10, s);
    sc25519_sq(_100, _10);
    sc25519_mul(_11, _10, s);
    sc25519_mul(_101, _10, _11);
    sc25519_mul(_111, _10, _101);
    sc25519_mul(_1001, _10, _111);
    sc25519_mul(_1011, _10, _1001);
    sc25519_mul(_1111, _100, _1011);
    sc25519_mul(recip, _1111, s);

    sc25519_sqmul(recip, 123 + 3, _101);
    sc25519_sqmul(recip, 2 + 2, _11);
    sc25519_sqmul(recip, 1 + 4, _1111);
    sc25519_sqmul(recip, 1 + 4, _1111);
    sc25519_sqmul(recip, 4, _1001);
    sc25519_sqmul(recip, 2, _11);
    sc25519_sqmul(recip, 1 + 4, _1111);
    sc25519_sqmul(recip, 1 + 3, _101);
    sc25519_sqmul(recip, 3 + 3, _101);
    sc25519_sqmul(recip, 3, _111);
    sc25519_sqmul(recip, 1 + 4, _1111);
    sc25519_sqmul(recip, 2 + 3, _111);
    sc25519_sqmul(recip, 2 + 2, _11);
    sc25519_sqmul(recip, 1 + 4, _1011);
    sc25519_sqmul(recip, 2 + 4, _1011);
    sc25519_sqmul(recip, 6 + 4, _1001);
    sc25519_sqmul(recip, 2 + 2, _11);
    sc25519_sqmul(recip, 3 + 2, _11);
    sc25519_sqmul(recip, 3 + 2, _11);
    sc25519_sqmul(recip, 1 + 4, _1001);
    sc25519_sqmul(recip, 1 + 3, _111);
    sc25519_sqmul(recip, 2 + 4, _1111);
    sc25519_sqmul(recip, 1 + 4, _1011);
    sc25519_sqmul(recip, 3, _101);
    sc25519_sqmul(recip, 2 + 4, _1111);
    sc25519_sqmul(recip, 3, _101);
    sc25519_sqmul(recip, 1 + 2, _11);
}