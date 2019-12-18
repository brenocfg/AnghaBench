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
struct resource {int dummy; } ;

/* Variables and functions */
 unsigned long ZTWO_PADDR (void*) ; 
 int /*<<< orphan*/  atomic_add (unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chipavail ; 
 int /*<<< orphan*/  chipram_res ; 
 int /*<<< orphan*/  kfree (struct resource*) ; 
 struct resource* lookup_resource (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,void*) ; 
 int /*<<< orphan*/  pr_err (char*,void*) ; 
 int /*<<< orphan*/  release_resource (struct resource*) ; 
 unsigned long resource_size (struct resource*) ; 

void amiga_chip_free(void *ptr)
{
	unsigned long start = ZTWO_PADDR(ptr);
	struct resource *res;
	unsigned long size;

	res = lookup_resource(&chipram_res, start);
	if (!res) {
		pr_err("amiga_chip_free: trying to free nonexistent region at "
		       "%p\n", ptr);
		return;
	}

	size = resource_size(res);
	pr_debug("amiga_chip_free: free %lu bytes at %p\n", size, ptr);
	atomic_add(size, &chipavail);
	release_resource(res);
	kfree(res);
}