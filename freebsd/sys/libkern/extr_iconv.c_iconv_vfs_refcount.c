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
struct vfsconf {scalar_t__ vfc_refcount; } ;

/* Variables and functions */
 int EBUSY ; 
 struct vfsconf* vfs_byname (char const*) ; 

int
iconv_vfs_refcount(const char *fsname)
{
	struct vfsconf *vfsp;

	vfsp = vfs_byname(fsname);
	if (vfsp != NULL && vfsp->vfc_refcount > 0)
		return (EBUSY);
	return (0);
}