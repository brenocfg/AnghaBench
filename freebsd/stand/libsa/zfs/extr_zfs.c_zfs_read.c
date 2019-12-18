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
struct zfsmount {int /*<<< orphan*/ * spa; } ;
struct stat {scalar_t__ st_size; } ;
struct open_file {scalar_t__ f_fsdata; scalar_t__ f_devdata; } ;
struct file {scalar_t__ f_seekp; int /*<<< orphan*/  f_dnode; } ;
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 int dnode_read (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,size_t,void*,size_t) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int zfs_stat (struct open_file*,struct stat*) ; 

__attribute__((used)) static int
zfs_read(struct open_file *f, void *start, size_t size, size_t *resid	/* out */)
{
	const spa_t *spa = ((struct zfsmount *)f->f_devdata)->spa;
	struct file *fp = (struct file *)f->f_fsdata;
	struct stat sb;
	size_t n;
	int rc;

	rc = zfs_stat(f, &sb);
	if (rc)
		return (rc);
	n = size;
	if (fp->f_seekp + n > sb.st_size)
		n = sb.st_size - fp->f_seekp;

	rc = dnode_read(spa, &fp->f_dnode, fp->f_seekp, start, n);
	if (rc)
		return (rc);

	if (0) {
	    int i;
	    for (i = 0; i < n; i++)
		putchar(((char*) start)[i]);
	}
	fp->f_seekp += n;
	if (resid)
		*resid = size - n;

	return (0);
}