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
typedef  int /*<<< orphan*/  const ge25519_p3 ;
typedef  int /*<<< orphan*/  ge25519_p2 ;
typedef  int /*<<< orphan*/  ge25519_p1p1 ;
typedef  int /*<<< orphan*/  ge25519_cached ;

/* Variables and functions */
 int /*<<< orphan*/  ge25519_add (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_cmov8_cached (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  ge25519_p1p1_to_p2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_p1p1_to_p3 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_p2_dbl (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_p3_0 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ge25519_p3_dbl (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ge25519_p3_to_cached (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

void
ge25519_scalarmult(ge25519_p3 *h, const unsigned char *a, const ge25519_p3 *p)
{
    signed char     e[64];
    signed char     carry;
    ge25519_p1p1    r;
    ge25519_p2      s;
    ge25519_p1p1    t2, t3, t4, t5, t6, t7, t8;
    ge25519_p3      p2, p3, p4, p5, p6, p7, p8;
    ge25519_cached  pi[8];
    ge25519_cached  t;
    int             i;

    ge25519_p3_to_cached(&pi[1 - 1], p);   /* p */

    ge25519_p3_dbl(&t2, p);
    ge25519_p1p1_to_p3(&p2, &t2);
    ge25519_p3_to_cached(&pi[2 - 1], &p2); /* 2p = 2*p */

    ge25519_add(&t3, p, &pi[2 - 1]);
    ge25519_p1p1_to_p3(&p3, &t3);
    ge25519_p3_to_cached(&pi[3 - 1], &p3); /* 3p = 2p+p */

    ge25519_p3_dbl(&t4, &p2);
    ge25519_p1p1_to_p3(&p4, &t4);
    ge25519_p3_to_cached(&pi[4 - 1], &p4); /* 4p = 2*2p */

    ge25519_add(&t5, p, &pi[4 - 1]);
    ge25519_p1p1_to_p3(&p5, &t5);
    ge25519_p3_to_cached(&pi[5 - 1], &p5); /* 5p = 4p+p */

    ge25519_p3_dbl(&t6, &p3);
    ge25519_p1p1_to_p3(&p6, &t6);
    ge25519_p3_to_cached(&pi[6 - 1], &p6); /* 6p = 2*3p */

    ge25519_add(&t7, p, &pi[6 - 1]);
    ge25519_p1p1_to_p3(&p7, &t7);
    ge25519_p3_to_cached(&pi[7 - 1], &p7); /* 7p = 6p+p */

    ge25519_p3_dbl(&t8, &p4);
    ge25519_p1p1_to_p3(&p8, &t8);
    ge25519_p3_to_cached(&pi[8 - 1], &p8); /* 8p = 2*4p */

    for (i = 0; i < 32; ++i) {
        e[2 * i + 0] = (a[i] >> 0) & 15;
        e[2 * i + 1] = (a[i] >> 4) & 15;
    }
    /* each e[i] is between 0 and 15 */
    /* e[63] is between 0 and 7 */

    carry = 0;
    for (i = 0; i < 63; ++i) {
        e[i] += carry;
        carry = e[i] + 8;
        carry >>= 4;
        e[i] -= carry * ((signed char) 1 << 4);
    }
    e[63] += carry;
    /* each e[i] is between -8 and 8 */

    ge25519_p3_0(h);

    for (i = 63; i != 0; i--) {
        ge25519_cmov8_cached(&t, pi, e[i]);
        ge25519_add(&r, h, &t);

        ge25519_p1p1_to_p2(&s, &r);
        ge25519_p2_dbl(&r, &s);
        ge25519_p1p1_to_p2(&s, &r);
        ge25519_p2_dbl(&r, &s);
        ge25519_p1p1_to_p2(&s, &r);
        ge25519_p2_dbl(&r, &s);
        ge25519_p1p1_to_p2(&s, &r);
        ge25519_p2_dbl(&r, &s);

        ge25519_p1p1_to_p3(h, &r);  /* *16 */
    }
    ge25519_cmov8_cached(&t, pi, e[i]);
    ge25519_add(&r, h, &t);

    ge25519_p1p1_to_p3(h, &r);
}