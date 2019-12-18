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
struct open_file {void* f_fsdata; } ;
struct file {struct file* f_fs; struct file* f_bg; struct file* f_buf; struct file** f_blk; } ;

/* Variables and functions */
 int EXT2_NIADDR ; 
 int /*<<< orphan*/  free (struct file*) ; 

__attribute__((used)) static int
ext2fs_close(struct open_file *f)
{
	struct file *fp = (struct file *)f->f_fsdata;
	int level;

	f->f_fsdata = (void *)0;
	if (fp == (struct file *)0)
		return (0);

	for (level = 0; level < EXT2_NIADDR; level++) {
		if (fp->f_blk[level])
			free(fp->f_blk[level]);
	}
	if (fp->f_buf)
		free(fp->f_buf);
	if (fp->f_bg)
		free(fp->f_bg);
	free(fp->f_fs);
	free(fp);
	return (0);
}