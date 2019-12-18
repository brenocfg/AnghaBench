#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ word_t ;
typedef  TYPE_1__* gf ;
typedef  int dword_t ;
typedef  int dsword_t ;
struct TYPE_6__ {scalar_t__* limb; } ;
struct TYPE_5__ {int* limb; } ;

/* Variables and functions */
 size_t LIMBPERM (unsigned int) ; 
 int LIMB_MASK (size_t) ; 
 int LIMB_PLACE_VALUE (size_t) ; 
 TYPE_4__* MODULUS ; 
 unsigned int NLIMBS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  gf_weak_reduce (TYPE_1__*) ; 

void gf_strong_reduce(gf a)
{
    dsword_t scarry;
    word_t scarry_0;
    dword_t carry = 0;
    unsigned int i;

    /* first, clear high */
    gf_weak_reduce(a);          /* Determined to have negligible perf impact. */

    /* now the total is less than 2p */

    /* compute total_value - p.  No need to reduce mod p. */
    scarry = 0;
    for (i = 0; i < NLIMBS; i++) {
        scarry = scarry + a->limb[LIMBPERM(i)] - MODULUS->limb[LIMBPERM(i)];
        a->limb[LIMBPERM(i)] = scarry & LIMB_MASK(LIMBPERM(i));
        scarry >>= LIMB_PLACE_VALUE(LIMBPERM(i));
    }

    /*
     * uncommon case: it was >= p, so now scarry = 0 and this = x common case:
     * it was < p, so now scarry = -1 and this = x - p + 2^255 so let's add
     * back in p.  will carry back off the top for 2^255.
     */
    assert(scarry == 0 || scarry == -1);

    scarry_0 = (word_t)scarry;

    /* add it back */
    for (i = 0; i < NLIMBS; i++) {
        carry =
            carry + a->limb[LIMBPERM(i)] +
            (scarry_0 & MODULUS->limb[LIMBPERM(i)]);
        a->limb[LIMBPERM(i)] = carry & LIMB_MASK(LIMBPERM(i));
        carry >>= LIMB_PLACE_VALUE(LIMBPERM(i));
    }

    assert(carry < 2 && ((word_t)carry + scarry_0) == 0);
}