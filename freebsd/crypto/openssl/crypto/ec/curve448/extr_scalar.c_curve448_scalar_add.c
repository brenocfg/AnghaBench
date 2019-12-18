#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* curve448_scalar_t ;
typedef  int c448_word_t ;
typedef  int c448_dword_t ;
struct TYPE_6__ {int* limb; } ;

/* Variables and functions */
 unsigned int C448_SCALAR_LIMBS ; 
 int WBITS ; 
 int /*<<< orphan*/  sc_p ; 
 int /*<<< orphan*/  sc_subx (TYPE_1__*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void curve448_scalar_add(curve448_scalar_t out, const curve448_scalar_t a,
                         const curve448_scalar_t b)
{
    c448_dword_t chain = 0;
    unsigned int i;

    for (i = 0; i < C448_SCALAR_LIMBS; i++) {
        chain = (chain + a->limb[i]) + b->limb[i];
        out->limb[i] = (c448_word_t)chain;
        chain >>= WBITS;
    }
    sc_subx(out, out->limb, sc_p, sc_p, (c448_word_t)chain);
}