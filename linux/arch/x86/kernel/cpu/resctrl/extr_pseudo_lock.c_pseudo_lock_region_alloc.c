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
struct pseudo_lock_region {scalar_t__ size; int /*<<< orphan*/  kmem; } ;

/* Variables and functions */
 int E2BIG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ KMALLOC_MAX_SIZE ; 
 int /*<<< orphan*/  kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pseudo_lock_region_clear (struct pseudo_lock_region*) ; 
 int pseudo_lock_region_init (struct pseudo_lock_region*) ; 
 int /*<<< orphan*/  rdt_last_cmd_puts (char*) ; 

__attribute__((used)) static int pseudo_lock_region_alloc(struct pseudo_lock_region *plr)
{
	int ret;

	ret = pseudo_lock_region_init(plr);
	if (ret < 0)
		return ret;

	/*
	 * We do not yet support contiguous regions larger than
	 * KMALLOC_MAX_SIZE.
	 */
	if (plr->size > KMALLOC_MAX_SIZE) {
		rdt_last_cmd_puts("Requested region exceeds maximum size\n");
		ret = -E2BIG;
		goto out_region;
	}

	plr->kmem = kzalloc(plr->size, GFP_KERNEL);
	if (!plr->kmem) {
		rdt_last_cmd_puts("Unable to allocate memory\n");
		ret = -ENOMEM;
		goto out_region;
	}

	ret = 0;
	goto out;
out_region:
	pseudo_lock_region_clear(plr);
out:
	return ret;
}