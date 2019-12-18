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
struct TYPE_2__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 unsigned long DEFAULT_MAP_WINDOW ; 
 unsigned long ENOMEM ; 
 unsigned long MAP_FIXED ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  kernel_managing_mpx_tables (int /*<<< orphan*/ ) ; 

unsigned long mpx_unmapped_area_check(unsigned long addr, unsigned long len,
		unsigned long flags)
{
	if (!kernel_managing_mpx_tables(current->mm))
		return addr;
	if (addr + len <= DEFAULT_MAP_WINDOW)
		return addr;
	if (flags & MAP_FIXED)
		return -ENOMEM;

	/*
	 * Requested len is larger than the whole area we're allowed to map in.
	 * Resetting hinting address wouldn't do much good -- fail early.
	 */
	if (len > DEFAULT_MAP_WINDOW)
		return -ENOMEM;

	/* Look for unmap area within DEFAULT_MAP_WINDOW */
	return 0;
}