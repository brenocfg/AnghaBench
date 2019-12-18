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
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 

struct dentry *apei_get_debugfs_dir(void)
{
	static struct dentry *dapei;

	if (!dapei)
		dapei = debugfs_create_dir("apei", NULL);

	return dapei;
}