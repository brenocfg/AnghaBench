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
struct hypfs_dbfs_file {int /*<<< orphan*/  lock; int /*<<< orphan*/  name; int /*<<< orphan*/  dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbfs_dir ; 
 int /*<<< orphan*/  dbfs_ops ; 
 int /*<<< orphan*/  debugfs_create_file (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct hypfs_dbfs_file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void hypfs_dbfs_create_file(struct hypfs_dbfs_file *df)
{
	df->dentry = debugfs_create_file(df->name, 0400, dbfs_dir, df,
					 &dbfs_ops);
	mutex_init(&df->lock);
}