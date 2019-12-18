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
struct vnode {int dummy; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 int ufs_extattrctl (struct mount*,int,struct vnode*,int,char const*) ; 
 int vfs_stdextattrctl (struct mount*,int,struct vnode*,int,char const*) ; 

__attribute__((used)) static int
ffs_extattrctl(struct mount *mp, int cmd, struct vnode *filename_vp,
	int attrnamespace, const char *attrname)
{

#ifdef UFS_EXTATTR
	return (ufs_extattrctl(mp, cmd, filename_vp, attrnamespace,
	    attrname));
#else
	return (vfs_stdextattrctl(mp, cmd, filename_vp, attrnamespace,
	    attrname));
#endif
}