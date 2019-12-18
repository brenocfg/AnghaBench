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
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ MALLOCSMART_SIZE_TO_SLICE (scalar_t__) ; 
 scalar_t__ MALLOCSMART_SLICES ; 
 unsigned int MALLOCSMART_SLICE_SIZE ; 
 int /*<<< orphan*/  XX_MallocSmartLock ; 
 scalar_t__ XX_MallocSmartMapCheck (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  XX_MallocSmartMapSet (unsigned int,scalar_t__) ; 
 scalar_t__ XX_MallocSmartPool ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void *
XX_MallocSmart(uint32_t size, int memPartitionId, uint32_t alignment)
{
	unsigned int i;
	vm_offset_t addr;

	addr = 0;

	/* Convert alignment and size to number of slices */
	alignment = MALLOCSMART_SIZE_TO_SLICE(alignment);
	size = MALLOCSMART_SIZE_TO_SLICE(size);

	/* Lock resources */
	mtx_lock(&XX_MallocSmartLock);

	/* Allocate region */
	for (i = 0; i + size <= MALLOCSMART_SLICES; i += alignment) {
		if (XX_MallocSmartMapCheck(i, size)) {
			XX_MallocSmartMapSet(i, size);
			addr = (vm_offset_t)XX_MallocSmartPool +
			    (i * MALLOCSMART_SLICE_SIZE);
			break;
		}
	}

	/* Unlock resources */
	mtx_unlock(&XX_MallocSmartLock);

	return ((void *)addr);
}