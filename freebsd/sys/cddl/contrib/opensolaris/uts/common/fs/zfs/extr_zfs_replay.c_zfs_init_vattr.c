#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int va_mode; int va_uid; int va_gid; int va_nodeid; int /*<<< orphan*/  va_rdev; int /*<<< orphan*/  va_type; scalar_t__ va_mask; } ;
typedef  TYPE_1__ vattr_t ;
typedef  scalar_t__ uint_t ;
typedef  int uint64_t ;
typedef  scalar_t__ uid_t ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int AT_GID ; 
 int AT_MODE ; 
 int AT_TYPE ; 
 int AT_UID ; 
 int /*<<< orphan*/  IFTOVT (int) ; 
 scalar_t__ IS_EPHEMERAL (int) ; 
 int MODEMASK ; 
 int /*<<< orphan*/  VATTR_NULL (TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_cmpldev (int) ; 

__attribute__((used)) static void
zfs_init_vattr(vattr_t *vap, uint64_t mask, uint64_t mode,
    uint64_t uid, uint64_t gid, uint64_t rdev, uint64_t nodeid)
{
	VATTR_NULL(vap);
	vap->va_mask = (uint_t)mask;
	if (mask & AT_TYPE)
		vap->va_type = IFTOVT(mode);
	if (mask & AT_MODE)
		vap->va_mode = mode & MODEMASK;
	if (mask & AT_UID)
		vap->va_uid = (uid_t)(IS_EPHEMERAL(uid)) ? -1 : uid;
	if (mask & AT_GID)
		vap->va_gid = (gid_t)(IS_EPHEMERAL(gid)) ? -1 : gid;
	vap->va_rdev = zfs_cmpldev(rdev);
	vap->va_nodeid = nodeid;
}