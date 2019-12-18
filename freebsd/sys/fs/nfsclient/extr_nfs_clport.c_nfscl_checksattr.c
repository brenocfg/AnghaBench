#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uid_t ;
struct TYPE_2__ {scalar_t__ tv_sec; } ;
struct vattr {scalar_t__ va_mode; scalar_t__ va_uid; scalar_t__ va_gid; scalar_t__ va_size; TYPE_1__ va_mtime; TYPE_1__ va_atime; int /*<<< orphan*/  va_vaflags; } ;
struct nfsvattr {scalar_t__ na_mode; scalar_t__ na_uid; scalar_t__ na_gid; scalar_t__ na_size; } ;
typedef  scalar_t__ mode_t ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  VA_UTIMES_NULL ; 
 scalar_t__ VNOVAL ; 
 int /*<<< orphan*/  vfs_timestamp (TYPE_1__*) ; 

int
nfscl_checksattr(struct vattr *vap, struct nfsvattr *nvap)
{

	if (vap->va_mode != (mode_t)VNOVAL) {
		if (vap->va_mode == nvap->na_mode)
			vap->va_mode = (mode_t)VNOVAL;
	}
	if (vap->va_uid != (uid_t)VNOVAL) {
		if (vap->va_uid == nvap->na_uid)
			vap->va_uid = (uid_t)VNOVAL;
	}
	if (vap->va_gid != (gid_t)VNOVAL) {
		if (vap->va_gid == nvap->na_gid)
			vap->va_gid = (gid_t)VNOVAL;
	}
	if (vap->va_size != VNOVAL) {
		if (vap->va_size == nvap->na_size)
			vap->va_size = VNOVAL;
	}

	/*
	 * We are normally called with only a partially initialized
	 * VAP.  Since the NFSv3 spec says that server may use the
	 * file attributes to store the verifier, the spec requires
	 * us to do a SETATTR RPC. FreeBSD servers store the verifier
	 * in atime, but we can't really assume that all servers will
	 * so we ensure that our SETATTR sets both atime and mtime.
	 * Set the VA_UTIMES_NULL flag for this case, so that
	 * the server's time will be used.  This is needed to
	 * work around a bug in some Solaris servers, where
	 * setting the time TOCLIENT causes the Setattr RPC
	 * to return NFS_OK, but not set va_mode.
	 */
	if (vap->va_mtime.tv_sec == VNOVAL) {
		vfs_timestamp(&vap->va_mtime);
		vap->va_vaflags |= VA_UTIMES_NULL;
	}
	if (vap->va_atime.tv_sec == VNOVAL)
		vap->va_atime = vap->va_mtime;
	return (1);
}