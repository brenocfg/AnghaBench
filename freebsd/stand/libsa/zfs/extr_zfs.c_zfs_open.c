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
struct zfsmount {int dummy; } ;
struct open_file {struct file* f_fsdata; int /*<<< orphan*/ * f_dev; scalar_t__ f_devdata; } ;
struct file {scalar_t__ f_seekp; int /*<<< orphan*/  f_dnode; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct file* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct file*) ; 
 int /*<<< orphan*/  zfs_dev ; 
 int zfs_lookup (struct zfsmount*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_open(const char *upath, struct open_file *f)
{
	struct zfsmount *mount = (struct zfsmount *)f->f_devdata;
	struct file *fp;
	int rc;

	if (f->f_dev != &zfs_dev)
		return (EINVAL);

	/* allocate file system specific data structure */
	fp = calloc(1, sizeof(struct file));
	if (fp == NULL)
		return (ENOMEM);
	f->f_fsdata = fp;

	rc = zfs_lookup(mount, upath, &fp->f_dnode);
	fp->f_seekp = 0;
	if (rc) {
		f->f_fsdata = NULL;
		free(fp);
	}
	return (rc);
}