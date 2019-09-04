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
 scalar_t__ checkpoint_requested ; 
 int /*<<< orphan*/  cycle_packfile () ; 
 int /*<<< orphan*/  dump_branches () ; 
 int /*<<< orphan*/  dump_marks () ; 
 int /*<<< orphan*/  dump_tags () ; 
 scalar_t__ object_count ; 

__attribute__((used)) static void checkpoint(void)
{
	checkpoint_requested = 0;
	if (object_count) {
		cycle_packfile();
	}
	dump_branches();
	dump_tags();
	dump_marks();
}