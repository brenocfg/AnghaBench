#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_mode; } ;
struct open_file {scalar_t__ f_fsdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  di_size; int /*<<< orphan*/  di_gid; int /*<<< orphan*/  di_uid; int /*<<< orphan*/  di_mode; } ;
struct file {TYPE_1__ f_di; } ;

/* Variables and functions */

__attribute__((used)) static int
ext2fs_stat(struct open_file *f, struct stat *sb)
{
	struct file *fp = (struct file *)f->f_fsdata;

	/* only important stuff */
	sb->st_mode = fp->f_di.di_mode;
	sb->st_uid = fp->f_di.di_uid;
	sb->st_gid = fp->f_di.di_gid;
	sb->st_size = fp->f_di.di_size;
	return (0);
}