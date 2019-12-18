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
struct vnode {struct mount* v_mount; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_REL (struct mount*) ; 
 int /*<<< orphan*/  M_VNODE_MARKER ; 
 int /*<<< orphan*/  free (struct vnode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mnt_vnode_markerfree_active(struct vnode **mvp, struct mount *mp)
{

	KASSERT((*mvp)->v_mount == mp, ("marker vnode mount list mismatch"));

	MNT_ILOCK(mp);
	MNT_REL(mp);
	MNT_IUNLOCK(mp);
	free(*mvp, M_VNODE_MARKER);
	*mvp = NULL;
}