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
struct stat {int st_mode; int /*<<< orphan*/  st_size; scalar_t__ st_gid; scalar_t__ st_uid; } ;
struct open_file {scalar_t__ f_fsdata; } ;
struct file {int f_flags; int /*<<< orphan*/  f_size; } ;

/* Variables and functions */
 int F_ISDIR ; 
 int S_IFDIR ; 
 int S_IFREG ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 

__attribute__((used)) static int
cd9660_stat(struct open_file *f, struct stat *sb)
{
	struct file *fp = (struct file *)f->f_fsdata;

	/* only important stuff */
	sb->st_mode = S_IRUSR | S_IRGRP | S_IROTH;
	if (fp->f_flags & F_ISDIR)
		sb->st_mode |= S_IFDIR;
	else
		sb->st_mode |= S_IFREG;
	sb->st_uid = sb->st_gid = 0;
	sb->st_size = fp->f_size;
	return 0;
}