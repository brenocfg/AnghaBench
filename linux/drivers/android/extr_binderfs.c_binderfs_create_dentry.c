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
 int /*<<< orphan*/  EEXIST ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct dentry* lookup_one_len (char const*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static struct dentry *binderfs_create_dentry(struct dentry *parent,
					     const char *name)
{
	struct dentry *dentry;

	dentry = lookup_one_len(name, parent, strlen(name));
	if (IS_ERR(dentry))
		return dentry;

	/* Return error if the file/dir already exists. */
	if (d_really_is_positive(dentry)) {
		dput(dentry);
		return ERR_PTR(-EEXIST);
	}

	return dentry;
}