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
struct bxe_fastpath {int /*<<< orphan*/  sge_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  bxe_clear_sge_mask_next_elems (struct bxe_fastpath*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline void
bxe_init_sge_ring_bit_mask(struct bxe_fastpath *fp)
{
    /* set the mask to all 1's, it's faster to compare to 0 than to 0xf's */
    memset(fp->sge_mask, 0xff, sizeof(fp->sge_mask));

    /*
     * Clear the two last indices in the page to 1. These are the indices that
     * correspond to the "next" element, hence will never be indicated and
     * should be removed from the calculations.
     */
    bxe_clear_sge_mask_next_elems(fp);
}