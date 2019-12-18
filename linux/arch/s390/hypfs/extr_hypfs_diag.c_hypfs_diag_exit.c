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
 int /*<<< orphan*/  dbfs_d204_file ; 
 int /*<<< orphan*/  dbfs_file_d204 ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diag204_free_buffer () ; 
 int /*<<< orphan*/  diag224_delete_name_table () ; 
 int /*<<< orphan*/  hypfs_dbfs_remove_file (int /*<<< orphan*/ *) ; 

void hypfs_diag_exit(void)
{
	debugfs_remove(dbfs_d204_file);
	diag224_delete_name_table();
	diag204_free_buffer();
	hypfs_dbfs_remove_file(&dbfs_file_d204);
}