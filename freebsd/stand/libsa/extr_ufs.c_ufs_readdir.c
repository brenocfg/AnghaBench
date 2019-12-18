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
struct open_file {scalar_t__ f_fsdata; } ;
struct file {scalar_t__ f_seekp; } ;
struct dirent {int /*<<< orphan*/  d_name; int /*<<< orphan*/  d_type; } ;
struct direct {scalar_t__ d_reclen; scalar_t__ d_ino; int /*<<< orphan*/  d_name; int /*<<< orphan*/  d_type; } ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 scalar_t__ DIP (struct file*,int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int buf_read_file (struct open_file*,char**,size_t*) ; 
 int /*<<< orphan*/  di_size ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ufs_readdir(struct open_file *f, struct dirent *d)
{
	struct file *fp = (struct file *)f->f_fsdata;
	struct direct *dp;
	char *buf;
	size_t buf_size;
	int error;

	/*
	 * assume that a directory entry will not be split across blocks
	 */
again:
	if (fp->f_seekp >= DIP(fp, di_size))
		return (ENOENT);
	error = buf_read_file(f, &buf, &buf_size);
	if (error)
		return (error);
	dp = (struct direct *)buf;
	fp->f_seekp += dp->d_reclen;
	if (dp->d_ino == (ino_t)0)
		goto again;
	d->d_type = dp->d_type;
	strcpy(d->d_name, dp->d_name);
	return (0);
}