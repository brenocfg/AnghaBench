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
struct vop_readlink_args {int /*<<< orphan*/  a_uio; TYPE_1__* a_vp; } ;
struct devfs_dirent {int /*<<< orphan*/  de_symlink; } ;
struct TYPE_2__ {struct devfs_dirent* v_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int uiomove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
devfs_readlink(struct vop_readlink_args *ap)
{
	struct devfs_dirent *de;

	de = ap->a_vp->v_data;
	return (uiomove(de->de_symlink, strlen(de->de_symlink), ap->a_uio));
}