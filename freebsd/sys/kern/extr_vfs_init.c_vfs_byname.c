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
struct vfsconf {int dummy; } ;

/* Variables and functions */
 struct vfsconf* vfs_byname_locked (char const*) ; 
 int /*<<< orphan*/  vfsconf_slock () ; 
 int /*<<< orphan*/  vfsconf_sunlock () ; 

struct vfsconf *
vfs_byname(const char *name)
{
	struct vfsconf *vfsp;

	vfsconf_slock();
	vfsp = vfs_byname_locked(name);
	vfsconf_sunlock();
	return (vfsp);
}