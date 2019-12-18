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
 int DIR_MODE ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  hypfs_add_dentry (struct dentry*) ; 
 struct dentry* hypfs_create_file (struct dentry*,char const*,int /*<<< orphan*/ *,int) ; 

struct dentry *hypfs_mkdir(struct dentry *parent, const char *name)
{
	struct dentry *dentry;

	dentry = hypfs_create_file(parent, name, NULL, S_IFDIR | DIR_MODE);
	if (IS_ERR(dentry))
		return dentry;
	hypfs_add_dentry(dentry);
	return dentry;
}