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
 int /*<<< orphan*/  BIT_VEC64_CLEAR_BIT (int /*<<< orphan*/ ,int) ; 
 int RX_SGE_NUM_PAGES ; 
 int RX_SGE_TOTAL_PER_PAGE ; 

__attribute__((used)) static inline void
bxe_clear_sge_mask_next_elems(struct bxe_fastpath *fp)
{
    int i, j;

    for (i = 1; i <= RX_SGE_NUM_PAGES; i++) {
        int idx = RX_SGE_TOTAL_PER_PAGE * i - 1;

        for (j = 0; j < 2; j++) {
            BIT_VEC64_CLEAR_BIT(fp->sge_mask, idx);
            idx--;
        }
    }
}