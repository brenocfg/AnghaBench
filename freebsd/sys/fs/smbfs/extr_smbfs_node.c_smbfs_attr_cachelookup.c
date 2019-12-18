#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vnode {scalar_t__ v_type; TYPE_3__* v_mount; } ;
struct vattr {scalar_t__ va_type; int va_mode; int va_nlink; int va_fileid; scalar_t__ va_vaflags; scalar_t__ va_filerev; int /*<<< orphan*/  va_size; int /*<<< orphan*/  va_bytes; int /*<<< orphan*/  va_rdev; int /*<<< orphan*/  va_flags; int /*<<< orphan*/  va_gen; int /*<<< orphan*/  va_mtime; int /*<<< orphan*/  va_ctime; int /*<<< orphan*/  va_atime; int /*<<< orphan*/  va_blocksize; int /*<<< orphan*/  va_fsid; int /*<<< orphan*/  va_gid; int /*<<< orphan*/  va_uid; } ;
struct smbnode {int n_attrage; int n_dosattr; int n_ino; int /*<<< orphan*/  n_mtime; int /*<<< orphan*/  n_size; } ;
struct smbmount {int sm_file_mode; int sm_dir_mode; int /*<<< orphan*/  sm_share; int /*<<< orphan*/  sm_gid; int /*<<< orphan*/  sm_uid; } ;
struct TYPE_8__ {int /*<<< orphan*/  vc_txmax; } ;
struct TYPE_5__ {int /*<<< orphan*/ * val; } ;
struct TYPE_6__ {TYPE_1__ f_fsid; } ;
struct TYPE_7__ {TYPE_2__ mnt_stat; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  NODEV ; 
 int SMB_FA_ARCHIVE ; 
 int SMB_FA_HIDDEN ; 
 int SMB_FA_RDONLY ; 
 int SMB_FA_SYSTEM ; 
 TYPE_4__* SSTOVC (int /*<<< orphan*/ ) ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  UF_ARCHIVE ; 
 int /*<<< orphan*/  UF_HIDDEN ; 
 int /*<<< orphan*/  UF_READONLY ; 
 int /*<<< orphan*/  UF_SYSTEM ; 
 scalar_t__ VDIR ; 
 int /*<<< orphan*/  VNOVAL ; 
 scalar_t__ VREG ; 
 struct smbnode* VTOSMB (struct vnode*) ; 
 struct smbmount* VTOSMBFS (struct vnode*) ; 
 int time_second ; 

int
smbfs_attr_cachelookup(struct vnode *vp, struct vattr *va)
{
	struct smbnode *np = VTOSMB(vp);
	struct smbmount *smp = VTOSMBFS(vp);
	int diff;

	diff = time_second - np->n_attrage;
	if (diff > 2)	/* XXX should be configurable */
		return ENOENT;
	va->va_type = vp->v_type;		/* vnode type (for create) */
	va->va_flags = 0;			/* flags defined for file */
	if (vp->v_type == VREG) {
		va->va_mode = smp->sm_file_mode; /* files access mode and type */
		if (np->n_dosattr & SMB_FA_RDONLY) {
			va->va_mode &= ~(S_IWUSR|S_IWGRP|S_IWOTH);
			va->va_flags |= UF_READONLY;
		}
	} else if (vp->v_type == VDIR) {
		va->va_mode = smp->sm_dir_mode;	/* files access mode and type */
	} else
		return EINVAL;
	va->va_size = np->n_size;
	va->va_nlink = 1;		/* number of references to file */
	va->va_uid = smp->sm_uid;	/* owner user id */
	va->va_gid = smp->sm_gid;	/* owner group id */
	va->va_fsid = vp->v_mount->mnt_stat.f_fsid.val[0];
	va->va_fileid = np->n_ino;	/* file id */
	if (va->va_fileid == 0)
		va->va_fileid = 2;
	va->va_blocksize = SSTOVC(smp->sm_share)->vc_txmax;
	va->va_mtime = np->n_mtime;
	va->va_atime = va->va_ctime = va->va_mtime;	/* time file changed */
	va->va_gen = VNOVAL;		/* generation number of file */
	if (np->n_dosattr & SMB_FA_HIDDEN)
		va->va_flags |= UF_HIDDEN;
	if (np->n_dosattr & SMB_FA_SYSTEM)
		va->va_flags |= UF_SYSTEM;
	/*
	 * We don't set the archive bit for directories.
	 */
	if ((vp->v_type != VDIR) && (np->n_dosattr & SMB_FA_ARCHIVE))
		va->va_flags |= UF_ARCHIVE;
	va->va_rdev = NODEV;		/* device the special file represents */
	va->va_bytes = va->va_size;	/* bytes of disk space held by file */
	va->va_filerev = 0;		/* file modification number */
	va->va_vaflags = 0;		/* operations flags */
	return 0;
}