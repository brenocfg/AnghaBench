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
typedef  int /*<<< orphan*/  ge25519_precomp ;
typedef  int /*<<< orphan*/  ge25519_p3 ;
typedef  int /*<<< orphan*/  ge25519_p2 ;
typedef  int /*<<< orphan*/  ge25519_p1p1 ;

/* Variables and functions */
 int /*<<< orphan*/  ge25519_cmov8_base (int /*<<< orphan*/ *,int,char) ; 
 int /*<<< orphan*/  ge25519_madd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_p1p1_to_p2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_p1p1_to_p3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_p2_dbl (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_p3_0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_p3_dbl (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ge25519_scalarmult_base(ge25519_p3 *h, const unsigned char *a)
{
    signed char     e[64];
    signed char     carry;
    ge25519_p1p1    r;
    ge25519_p2      s;
    ge25519_precomp t;
    int             i;

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

    for (i = 1; i < 64; i += 2) {
        ge25519_cmov8_base(&t, i / 2, e[i]);
        ge25519_madd(&r, h, &t);
        ge25519_p1p1_to_p3(h, &r);
    }

    ge25519_p3_dbl(&r, h);
    ge25519_p1p1_to_p2(&s, &r);
    ge25519_p2_dbl(&r, &s);
    ge25519_p1p1_to_p2(&s, &r);
    ge25519_p2_dbl(&r, &s);
    ge25519_p1p1_to_p2(&s, &r);
    ge25519_p2_dbl(&r, &s);
    ge25519_p1p1_to_p3(h, &r);

    for (i = 0; i < 64; i += 2) {
        ge25519_cmov8_base(&t, i / 2, e[i]);
        ge25519_madd(&r, h, &t);
        ge25519_p1p1_to_p3(h, &r);
    }
}