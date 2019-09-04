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
struct TYPE_7__ {int /*<<< orphan*/  xy2d; int /*<<< orphan*/  yplusx; int /*<<< orphan*/  yminusx; } ;
typedef  TYPE_1__ const ge25519_precomp ;

/* Variables and functions */
 unsigned char const equal (unsigned char const,int) ; 
 int /*<<< orphan*/  fe25519_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe25519_neg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ge25519_cmov (TYPE_1__ const*,TYPE_1__ const*,unsigned char const) ; 
 int /*<<< orphan*/  ge25519_precomp_0 (TYPE_1__ const*) ; 
 unsigned char negative (char const) ; 

__attribute__((used)) static void
ge25519_cmov8(ge25519_precomp *t, const ge25519_precomp precomp[8], const signed char b)
{
    ge25519_precomp     minust;
    const unsigned char bnegative = negative(b);
    const unsigned char babs      = b - (((-bnegative) & b) * ((signed char) 1 << 1));

    ge25519_precomp_0(t);
    ge25519_cmov(t, &precomp[0], equal(babs, 1));
    ge25519_cmov(t, &precomp[1], equal(babs, 2));
    ge25519_cmov(t, &precomp[2], equal(babs, 3));
    ge25519_cmov(t, &precomp[3], equal(babs, 4));
    ge25519_cmov(t, &precomp[4], equal(babs, 5));
    ge25519_cmov(t, &precomp[5], equal(babs, 6));
    ge25519_cmov(t, &precomp[6], equal(babs, 7));
    ge25519_cmov(t, &precomp[7], equal(babs, 8));
    fe25519_copy(minust.yplusx, t->yminusx);
    fe25519_copy(minust.yminusx, t->yplusx);
    fe25519_neg(minust.xy2d, t->xy2d);
    ge25519_cmov(t, &minust, bnegative);
}