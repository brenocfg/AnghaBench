#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* v_data; } ;
typedef  TYPE_1__ vnode_t ;
struct TYPE_9__ {int va_nlink; int /*<<< orphan*/  va_nodeid; scalar_t__ va_flags; int /*<<< orphan*/  va_atime; int /*<<< orphan*/  va_type; int /*<<< orphan*/  va_mode; scalar_t__ va_seq; scalar_t__ va_nblocks; scalar_t__ va_blksize; scalar_t__ va_rdev; scalar_t__ va_gid; scalar_t__ va_uid; } ;
typedef  TYPE_2__ vattr_t ;
typedef  int /*<<< orphan*/  timestruc_t ;
struct TYPE_10__ {int /*<<< orphan*/  sn_id; } ;
typedef  TYPE_3__ sfs_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  VDIR ; 
 int /*<<< orphan*/  gethrestime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vn_fsid (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  zfsctl_ctldir_mode ; 

__attribute__((used)) static void
zfsctl_common_getattr(vnode_t *vp, vattr_t *vap)
{
	timestruc_t	now;
	sfs_node_t *node;

	node = vp->v_data;

	vap->va_uid = 0;
	vap->va_gid = 0;
	vap->va_rdev = 0;
	/*
	 * We are a purely virtual object, so we have no
	 * blocksize or allocated blocks.
	 */
	vap->va_blksize = 0;
	vap->va_nblocks = 0;
	vap->va_seq = 0;
	vn_fsid(vp, vap);
	vap->va_mode = zfsctl_ctldir_mode;
	vap->va_type = VDIR;
	/*
	 * We live in the now (for atime).
	 */
	gethrestime(&now);
	vap->va_atime = now;
	/* FreeBSD: Reset chflags(2) flags. */
	vap->va_flags = 0;

	vap->va_nodeid = node->sn_id;

	/* At least '.' and '..'. */
	vap->va_nlink = 2;
}