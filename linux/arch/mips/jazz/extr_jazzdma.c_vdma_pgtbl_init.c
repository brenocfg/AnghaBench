#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long frame; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 scalar_t__ VDMA_PAGESIZE ; 
 int /*<<< orphan*/  VDMA_PAGE_EMPTY ; 
 int VDMA_PGTBL_ENTRIES ; 
 TYPE_1__* pgtbl ; 

__attribute__((used)) static inline void vdma_pgtbl_init(void)
{
	unsigned long paddr = 0;
	int i;

	for (i = 0; i < VDMA_PGTBL_ENTRIES; i++) {
		pgtbl[i].frame = paddr;
		pgtbl[i].owner = VDMA_PAGE_EMPTY;
		paddr += VDMA_PAGESIZE;
	}
}