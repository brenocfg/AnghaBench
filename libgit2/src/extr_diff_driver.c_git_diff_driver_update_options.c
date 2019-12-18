#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int binary_flags; int other_flags; } ;
typedef  TYPE_1__ git_diff_driver ;

/* Variables and functions */
 int FORCE_DIFFABLE ; 

void git_diff_driver_update_options(
	uint32_t *option_flags, git_diff_driver *driver)
{
	if ((*option_flags & FORCE_DIFFABLE) == 0)
		*option_flags |= driver->binary_flags;

	*option_flags |= driver->other_flags;
}