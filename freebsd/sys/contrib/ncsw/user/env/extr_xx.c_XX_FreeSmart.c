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
typedef  scalar_t__ p ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 unsigned int MALLOCSMART_SIZE_TO_SLICE (scalar_t__) ; 
 int /*<<< orphan*/  XX_MallocSmartLock ; 
 unsigned int* XX_MallocSmartMap ; 
 int /*<<< orphan*/  XX_MallocSmartMapClear (unsigned int,unsigned int) ; 
 scalar_t__ XX_MallocSmartPool ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
XX_FreeSmart(void *p)
{
	unsigned int start, slices;

	/* Calculate first slice of region */
	start = MALLOCSMART_SIZE_TO_SLICE((vm_offset_t)(p) -
	    (vm_offset_t)XX_MallocSmartPool);

	/* Lock resources */
	mtx_lock(&XX_MallocSmartLock);

	KASSERT(XX_MallocSmartMap[start] > 0,
	    ("XX_FreeSmart: Double or mid-block free!\n"));

	/* Free region */
	slices = XX_MallocSmartMap[start];
	XX_MallocSmartMapClear(start, slices);

	/* Unlock resources */
	mtx_unlock(&XX_MallocSmartLock);
}