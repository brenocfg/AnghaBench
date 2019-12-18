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
struct vnode {int /*<<< orphan*/  v_mount; } ;
struct statfs {scalar_t__ f_ffree; int /*<<< orphan*/  f_bavail; int /*<<< orphan*/  f_bsize; int /*<<< orphan*/  f_bfree; int /*<<< orphan*/  f_blocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NFSEXITCODE (int) ; 
 int VFS_STATFS (int /*<<< orphan*/ ,struct statfs*) ; 
 int /*<<< orphan*/  free (struct statfs*,int /*<<< orphan*/ ) ; 
 struct statfs* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nfsrv_devidcnt ; 
 int nfsrv_pnfsstatfs (struct statfs*,int /*<<< orphan*/ ) ; 

int
nfsvno_statfs(struct vnode *vp, struct statfs *sf)
{
	struct statfs *tsf;
	int error;

	tsf = NULL;
	if (nfsrv_devidcnt > 0) {
		/* For a pNFS service, get the DS numbers. */
		tsf = malloc(sizeof(*tsf), M_TEMP, M_WAITOK | M_ZERO);
		error = nfsrv_pnfsstatfs(tsf, vp->v_mount);
		if (error != 0) {
			free(tsf, M_TEMP);
			tsf = NULL;
		}
	}
	error = VFS_STATFS(vp->v_mount, sf);
	if (error == 0) {
		if (tsf != NULL) {
			sf->f_blocks = tsf->f_blocks;
			sf->f_bavail = tsf->f_bavail;
			sf->f_bfree = tsf->f_bfree;
			sf->f_bsize = tsf->f_bsize;
		}
		/*
		 * Since NFS handles these values as unsigned on the
		 * wire, there is no way to represent negative values,
		 * so set them to 0. Without this, they will appear
		 * to be very large positive values for clients like
		 * Solaris10.
		 */
		if (sf->f_bavail < 0)
			sf->f_bavail = 0;
		if (sf->f_ffree < 0)
			sf->f_ffree = 0;
	}
	free(tsf, M_TEMP);
	NFSEXITCODE(error);
	return (error);
}