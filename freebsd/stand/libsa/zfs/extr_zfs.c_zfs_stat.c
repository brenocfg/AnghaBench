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
struct stat {int dummy; } ;
struct open_file {scalar_t__ f_fsdata; scalar_t__ f_devdata; } ;
struct file {int /*<<< orphan*/  f_dnode; } ;
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 int zfs_dnode_stat (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,struct stat*) ; 

__attribute__((used)) static int
zfs_stat(struct open_file *f, struct stat *sb)
{
	const spa_t *spa = ((struct zfsmount *)f->f_devdata)->spa;
	struct file *fp = (struct file *)f->f_fsdata;

	return (zfs_dnode_stat(spa, &fp->f_dnode, sb));
}