#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int* ui; } ;
typedef  TYPE_1__ addr64 ;
struct TYPE_5__ {int size; unsigned int ea_low; } ;

/* Variables and functions */
 scalar_t__ LSCSA_BYTE_OFFSET (int /*<<< orphan*/ ) ; 
 TYPE_2__* dma_list ; 
 int /*<<< orphan*/ * ls ; 

__attribute__((used)) static inline void build_dma_list(addr64 lscsa_ea)
{
	unsigned int ea_low;
	int i;

	/* Save, Step 6:
	 * Restore, Step 3:
	 *    Update the effective address for the CSA in the
	 *    pre-canned DMA-list in local storage.
	 */
	ea_low = lscsa_ea.ui[1];
	ea_low += LSCSA_BYTE_OFFSET(ls[16384]);

	for (i = 0; i < 15; i++, ea_low += 16384) {
		dma_list[i].size = 16384;
		dma_list[i].ea_low = ea_low;
	}
}