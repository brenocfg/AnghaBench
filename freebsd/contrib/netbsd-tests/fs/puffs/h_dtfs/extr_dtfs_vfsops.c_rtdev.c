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
struct vattr {int va_nlink; int /*<<< orphan*/  va_rdev; int /*<<< orphan*/  va_mode; } ;
struct puffs_usermount {int dummy; } ;
struct puffs_node {struct vattr pn_va; } ;
typedef  enum vtype { ____Placeholder_vtype } vtype ;

/* Variables and functions */
 int /*<<< orphan*/  S_IFBLK ; 
 int /*<<< orphan*/  S_IFCHR ; 
 int VBLK ; 
 int /*<<< orphan*/  dtfs_baseattrs (struct vattr*,int,int) ; 
 int /*<<< orphan*/  makedev (int,int) ; 
 struct puffs_node* puffs_getroot (struct puffs_usermount*) ; 
 int /*<<< orphan*/  puffs_setrootinfo (struct puffs_usermount*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sscanf (char const*,char*,int*,int*) ; 

__attribute__((used)) static int
rtdev(struct puffs_usermount *pu, const char *str, enum vtype vt)
{
	struct puffs_node *pn = puffs_getroot(pu);
	struct vattr *va = &pn->pn_va;
	int major, minor;

	if (sscanf(str, "%*s %d %d", &major, &minor) != 2)
		return 1;

	dtfs_baseattrs(va, vt, 2);
	va->va_nlink = 1;
	va->va_rdev = makedev(major, minor);

	if (vt == VBLK)
		va->va_mode |= S_IFBLK;
	else
		va->va_mode |= S_IFCHR;

	puffs_setrootinfo(pu, vt, 0, va->va_rdev);

	return 0;
}