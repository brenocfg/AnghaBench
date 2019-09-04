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
struct TYPE_2__ {int /*<<< orphan*/ * gmalloc; } ;

/* Variables and functions */
 TYPE_1__ git__allocator ; 
 int setup_default_allocator () ; 

int git_allocator_global_init(void)
{
	/*
	 * We don't want to overwrite any allocator which has been set before
	 * the init function is called.
	 */
	if (git__allocator.gmalloc != NULL)
		return 0;

	return setup_default_allocator();
}