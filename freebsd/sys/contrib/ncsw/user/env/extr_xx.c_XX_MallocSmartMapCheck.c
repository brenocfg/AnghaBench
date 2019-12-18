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

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int TRUE ; 
 int /*<<< orphan*/  XX_MallocSmartLock ; 
 scalar_t__* XX_MallocSmartMap ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
XX_MallocSmartMapCheck(unsigned int start, unsigned int slices)
{
	unsigned int i;

	mtx_assert(&XX_MallocSmartLock, MA_OWNED);
	for (i = start; i < start + slices; i++)
		if (XX_MallocSmartMap[i])
			return (FALSE);
	return (TRUE);
}