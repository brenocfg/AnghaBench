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
typedef  int /*<<< orphan*/  pt2_entry_t ;

/* Variables and functions */
 int NPTE2_IN_PT2 ; 
 scalar_t__ PTE2_SIZE ; 
 int /*<<< orphan*/  pte2_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
pmap_fill_pt2(pt2_entry_t *fpte2p, pt2_entry_t npte2)
{
	pt2_entry_t *pte2p;

	for (pte2p = fpte2p; pte2p < fpte2p + NPTE2_IN_PT2; pte2p++) {
		pte2_store(pte2p, npte2);
		npte2 += PTE2_SIZE;
	}
}