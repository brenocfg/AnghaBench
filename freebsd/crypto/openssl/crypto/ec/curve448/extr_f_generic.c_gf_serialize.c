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
typedef  scalar_t__ uint8_t ;
typedef  TYPE_1__* gf ;
typedef  unsigned int dword_t ;
struct TYPE_7__ {scalar_t__* limb; } ;

/* Variables and functions */
 size_t LIMBPERM (unsigned int) ; 
 scalar_t__ LIMB_PLACE_VALUE (size_t) ; 
 unsigned int NLIMBS ; 
 int SER_BYTES ; 
 int X_SER_BYTES ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  gf_copy (TYPE_1__*,TYPE_1__* const) ; 
 scalar_t__ gf_hibit (TYPE_1__*) ; 
 int /*<<< orphan*/  gf_strong_reduce (TYPE_1__*) ; 

void gf_serialize(uint8_t serial[SER_BYTES], const gf x, int with_hibit)
{
    unsigned int j = 0, fill = 0;
    dword_t buffer = 0;
    int i;
    gf red;

    gf_copy(red, x);
    gf_strong_reduce(red);
    if (!with_hibit)
        assert(gf_hibit(red) == 0);

    for (i = 0; i < (with_hibit ? X_SER_BYTES : SER_BYTES); i++) {
        if (fill < 8 && j < NLIMBS) {
            buffer |= ((dword_t) red->limb[LIMBPERM(j)]) << fill;
            fill += LIMB_PLACE_VALUE(LIMBPERM(j));
            j++;
        }
        serial[i] = (uint8_t)buffer;
        fill -= 8;
        buffer >>= 8;
    }
}