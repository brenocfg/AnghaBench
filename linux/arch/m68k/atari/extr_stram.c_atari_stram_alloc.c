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
struct resource {char const* name; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long PAGE_ALIGN (unsigned long) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int allocate_resource (int /*<<< orphan*/ *,struct resource*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* atari_stram_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct resource*) ; 
 struct resource* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  stram_pool ; 

void *atari_stram_alloc(unsigned long size, const char *owner)
{
	struct resource *res;
	int error;

	pr_debug("atari_stram_alloc: allocate %lu bytes\n", size);

	/* round up */
	size = PAGE_ALIGN(size);

	res = kzalloc(sizeof(struct resource), GFP_KERNEL);
	if (!res)
		return NULL;

	res->name = owner;
	error = allocate_resource(&stram_pool, res, size, 0, UINT_MAX,
				  PAGE_SIZE, NULL, NULL);
	if (error < 0) {
		pr_err("atari_stram_alloc: allocate_resource() failed %d!\n",
		       error);
		kfree(res);
		return NULL;
	}

	pr_debug("atari_stram_alloc: returning %pR\n", res);
	return atari_stram_to_virt(res->start);
}