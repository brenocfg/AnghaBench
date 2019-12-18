#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vnode {int dummy; } ;
struct netexport {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  f_fsid; } ;
struct mount {TYPE_1__ mnt_stat; } ;
struct export_args {int /*<<< orphan*/ * ex_indexfile; } ;
struct TYPE_6__ {int /*<<< orphan*/  fh_fid; int /*<<< orphan*/  fh_fsid; } ;
struct TYPE_5__ {int np_valid; char* np_index; struct mount* np_mount; TYPE_3__ np_handle; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 scalar_t__ MAXNAMLEN ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int VFS_ROOT (struct mount*,int /*<<< orphan*/ ,struct vnode**) ; 
 int VOP_VPTOFH (struct vnode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 int copyinstr (int /*<<< orphan*/ *,char*,scalar_t__,size_t*) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ nfs_pub ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 

int
vfs_setpublicfs(struct mount *mp, struct netexport *nep,
    struct export_args *argp)
{
	int error;
	struct vnode *rvp;
	char *cp;

	/*
	 * mp == NULL -> invalidate the current info, the FS is
	 * no longer exported. May be called from either vfs_export
	 * or unmount, so check if it hasn't already been done.
	 */
	if (mp == NULL) {
		if (nfs_pub.np_valid) {
			nfs_pub.np_valid = 0;
			if (nfs_pub.np_index != NULL) {
				free(nfs_pub.np_index, M_TEMP);
				nfs_pub.np_index = NULL;
			}
		}
		return (0);
	}

	/*
	 * Only one allowed at a time.
	 */
	if (nfs_pub.np_valid != 0 && mp != nfs_pub.np_mount)
		return (EBUSY);

	/*
	 * Get real filehandle for root of exported FS.
	 */
	bzero(&nfs_pub.np_handle, sizeof(nfs_pub.np_handle));
	nfs_pub.np_handle.fh_fsid = mp->mnt_stat.f_fsid;

	if ((error = VFS_ROOT(mp, LK_EXCLUSIVE, &rvp)))
		return (error);

	if ((error = VOP_VPTOFH(rvp, &nfs_pub.np_handle.fh_fid)))
		return (error);

	vput(rvp);

	/*
	 * If an indexfile was specified, pull it in.
	 */
	if (argp->ex_indexfile != NULL) {
		if (nfs_pub.np_index == NULL)
			nfs_pub.np_index = malloc(MAXNAMLEN + 1, M_TEMP,
			    M_WAITOK);
		error = copyinstr(argp->ex_indexfile, nfs_pub.np_index,
		    MAXNAMLEN, (size_t *)0);
		if (!error) {
			/*
			 * Check for illegal filenames.
			 */
			for (cp = nfs_pub.np_index; *cp; cp++) {
				if (*cp == '/') {
					error = EINVAL;
					break;
				}
			}
		}
		if (error) {
			free(nfs_pub.np_index, M_TEMP);
			nfs_pub.np_index = NULL;
			return (error);
		}
	}

	nfs_pub.np_mount = mp;
	nfs_pub.np_valid = 1;
	return (0);
}