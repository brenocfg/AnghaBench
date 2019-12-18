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
 int /*<<< orphan*/  kernel_ptdump_info ; 
 int /*<<< orphan*/  ptdump_debugfs_register (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ptdump_initialize () ; 

__attribute__((used)) static int ptdump_init(void)
{
	ptdump_initialize();
	ptdump_debugfs_register(&kernel_ptdump_info, "kernel_page_tables");
	return 0;
}