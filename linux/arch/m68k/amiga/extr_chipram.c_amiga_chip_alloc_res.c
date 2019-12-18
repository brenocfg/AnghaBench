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
struct resource {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 unsigned long PAGE_ALIGN (unsigned long) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  UINT_MAX ; 
 void* ZTWO_VADDR (int /*<<< orphan*/ ) ; 
 int allocate_resource (int /*<<< orphan*/ *,struct resource*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chipavail ; 
 int /*<<< orphan*/  chipram_res ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

void *amiga_chip_alloc_res(unsigned long size, struct resource *res)
{
	int error;

	/* round up */
	size = PAGE_ALIGN(size);

	pr_debug("amiga_chip_alloc_res: allocate %lu bytes\n", size);
	error = allocate_resource(&chipram_res, res, size, 0, UINT_MAX,
				  PAGE_SIZE, NULL, NULL);
	if (error < 0) {
		pr_err("amiga_chip_alloc_res: allocate_resource() failed %d!\n",
		       error);
		return NULL;
	}

	atomic_sub(size, &chipavail);
	pr_debug("amiga_chip_alloc_res: returning %pR\n", res);
	return ZTWO_VADDR(res->start);
}