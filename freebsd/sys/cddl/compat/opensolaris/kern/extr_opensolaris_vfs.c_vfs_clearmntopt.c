#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  mnt_opt; } ;
typedef  TYPE_1__ vfs_t ;

/* Variables and functions */
 int /*<<< orphan*/  MNT_ILOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  MNT_MTX (TYPE_1__*) ; 
 int mtx_owned (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_deleteopt (int /*<<< orphan*/ ,char const*) ; 

void
vfs_clearmntopt(vfs_t *vfsp, const char *name)
{
	int locked;

	if (!(locked = mtx_owned(MNT_MTX(vfsp))))
		MNT_ILOCK(vfsp);
	vfs_deleteopt(vfsp->mnt_opt, name);
	if (!locked)
		MNT_IUNLOCK(vfsp);
}