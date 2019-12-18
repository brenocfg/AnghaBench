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
struct tarfile {int tf_size; } ;
struct stat {int st_size; int st_blocks; int /*<<< orphan*/  st_mode; } ;
struct open_file {scalar_t__ f_fsdata; } ;

/* Variables and functions */
 int EBADF ; 
 int /*<<< orphan*/  get_mode (struct tarfile*) ; 
 int /*<<< orphan*/  memset (struct stat*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
pkg_stat(struct open_file *f, struct stat *sb)
{
	struct tarfile *tf;

	tf = (struct tarfile *)f->f_fsdata;
	if (tf == NULL)
		return (EBADF);
	memset(sb, 0, sizeof(*sb));
	sb->st_mode = get_mode(tf);
	sb->st_size = tf->tf_size;
	sb->st_blocks = (tf->tf_size + 511) / 512;
	return (0);
}