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
 int /*<<< orphan*/  PTE_RDONLY ; 
 int /*<<< orphan*/  PTE_WRITE ; 
 int /*<<< orphan*/  __pgprot (int /*<<< orphan*/ ) ; 
 int change_memory_common (unsigned long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int set_memory_ro(unsigned long addr, int numpages)
{
	return change_memory_common(addr, numpages,
					__pgprot(PTE_RDONLY),
					__pgprot(PTE_WRITE));
}