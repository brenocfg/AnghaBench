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
 int /*<<< orphan*/ * ag71xx_debugfs_root ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ *) ; 

void ag71xx_debugfs_root_exit(void)
{
	debugfs_remove(ag71xx_debugfs_root);
	ag71xx_debugfs_root = NULL;
}