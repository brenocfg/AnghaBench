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
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_initialized () ; 
 int /*<<< orphan*/ * hzip_debugfs_root ; 

__attribute__((used)) static void hisi_zip_register_debugfs(void)
{
	if (!debugfs_initialized())
		return;

	hzip_debugfs_root = debugfs_create_dir("hisi_zip", NULL);
	if (IS_ERR_OR_NULL(hzip_debugfs_root))
		hzip_debugfs_root = NULL;
}