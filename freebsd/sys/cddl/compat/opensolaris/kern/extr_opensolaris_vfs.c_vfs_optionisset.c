#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct vfsoptlist* mnt_optnew; } ;
typedef  TYPE_1__ vfs_t ;
struct vfsoptlist {int dummy; } ;

/* Variables and functions */
 int vfs_getopt (struct vfsoptlist*,char const*,void**,int /*<<< orphan*/ *) ; 

int
vfs_optionisset(const vfs_t *vfsp, const char *opt, char **argp)
{
	struct vfsoptlist *opts = vfsp->mnt_optnew;
	int error;

	if (opts == NULL)
		return (0);
	error = vfs_getopt(opts, opt, (void **)argp, NULL);
	return (error != 0 ? 0 : 1);
}