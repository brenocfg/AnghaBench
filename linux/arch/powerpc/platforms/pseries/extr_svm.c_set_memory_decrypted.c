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
 int EINVAL ; 
 int /*<<< orphan*/  PAGE_ALIGNED (unsigned long) ; 
 int /*<<< orphan*/  PHYS_PFN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pa (unsigned long) ; 
 int /*<<< orphan*/  uv_share_page (int /*<<< orphan*/ ,int) ; 

int set_memory_decrypted(unsigned long addr, int numpages)
{
	if (!PAGE_ALIGNED(addr))
		return -EINVAL;

	uv_share_page(PHYS_PFN(__pa(addr)), numpages);

	return 0;
}