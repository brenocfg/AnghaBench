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
struct cd9660_ino_alloc_arg {scalar_t__ i_ino; scalar_t__ ino; int /*<<< orphan*/  ep; } ;

/* Variables and functions */
 int cd9660_vget_internal (struct mount*,scalar_t__,int,struct vnode**,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cd9660_ino_alloc(struct mount *mp, void *arg, int lkflags,
    struct vnode **vpp)
{
	struct cd9660_ino_alloc_arg *dd_arg;

	dd_arg = arg;
	return (cd9660_vget_internal(mp, dd_arg->i_ino, lkflags, vpp,
	    dd_arg->i_ino != dd_arg->ino, dd_arg->ep));
}