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
struct udf_mnt {int /*<<< orphan*/  root_icb; } ;
struct mount {int dummy; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 struct udf_mnt* VFSTOUDFFS (struct mount*) ; 
 int /*<<< orphan*/  udf_getid (int /*<<< orphan*/ *) ; 
 int udf_vget (struct mount*,int /*<<< orphan*/ ,int,struct vnode**) ; 

__attribute__((used)) static int
udf_root(struct mount *mp, int flags, struct vnode **vpp)
{
	struct udf_mnt *udfmp;
	ino_t id;

	udfmp = VFSTOUDFFS(mp);

	id = udf_getid(&udfmp->root_icb);

	return (udf_vget(mp, id, flags, vpp));
}