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
struct vnode {int /*<<< orphan*/  v_mount; } ;
struct uio {long uio_offset; long uio_resid; int /*<<< orphan*/  uio_td; } ;
struct ucred {int dummy; } ;
struct smbnode {int n_name; int n_ino; int n_parentino; long n_dirofs; struct smbfs_fctx* n_dirseq; scalar_t__ n_parent; } ;
struct TYPE_2__ {int fa_ino; int fa_attr; } ;
struct smbfs_fctx {long f_nmlen; TYPE_1__ f_attr; int /*<<< orphan*/  f_name; } ;
struct smb_cred {int dummy; } ;
struct dirent {long d_reclen; int d_fileno; long d_namlen; char* d_name; void* d_type; } ;
struct componentname {char* cn_nameptr; long cn_namelen; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 long DE_SIZE ; 
 void* DT_DIR ; 
 void* DT_REG ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  SMBVDEBUG (char*,int,...) ; 
 int SMB_FA_DIR ; 
 int SMB_FA_HIDDEN ; 
 int SMB_FA_SYSTEM ; 
 struct smbnode* VTOSMB (struct vnode*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,char*,long) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  cache_enter (struct vnode*,struct vnode*,struct componentname*) ; 
 int /*<<< orphan*/  dirent_terminate (struct dirent*) ; 
 int /*<<< orphan*/  smb_makescred (struct smb_cred*,int /*<<< orphan*/ ,struct ucred*) ; 
 scalar_t__ smbfs_fastlookup ; 
 int /*<<< orphan*/  smbfs_findclose (struct smbfs_fctx*,struct smb_cred*) ; 
 int smbfs_findnext (struct smbfs_fctx*,long,struct smb_cred*) ; 
 int smbfs_findopen (struct smbnode*,char*,int,int,struct smb_cred*,struct smbfs_fctx**) ; 
 int /*<<< orphan*/  smbfs_free_scred (struct smb_cred*) ; 
 struct smb_cred* smbfs_malloc_scred () ; 
 int smbfs_nget (int /*<<< orphan*/ ,struct vnode*,int /*<<< orphan*/ ,long,TYPE_1__*,struct vnode**) ; 
 int uiomove (struct dirent*,long,struct uio*) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 

__attribute__((used)) static int
smbfs_readvdir(struct vnode *vp, struct uio *uio, struct ucred *cred)
{
	struct dirent de;
	struct componentname cn;
	struct smb_cred *scred;
	struct smbfs_fctx *ctx;
	struct vnode *newvp;
	struct smbnode *np = VTOSMB(vp);
	int error/*, *eofflag = ap->a_eofflag*/;
	long offset, limit;

	np = VTOSMB(vp);
	SMBVDEBUG("dirname='%s'\n", np->n_name);
	scred = smbfs_malloc_scred();
	smb_makescred(scred, uio->uio_td, cred);
	offset = uio->uio_offset / DE_SIZE;	/* offset in the directory */
	limit = uio->uio_resid / DE_SIZE;
	if (uio->uio_resid < DE_SIZE || uio->uio_offset < 0) {
		error = EINVAL;
		goto out;
	}
	while (limit && offset < 2) {
		limit--;
		bzero((caddr_t)&de, DE_SIZE);
		de.d_reclen = DE_SIZE;
		de.d_fileno = (offset == 0) ? np->n_ino :
		    (np->n_parent ? np->n_parentino : 2);
		if (de.d_fileno == 0)
			de.d_fileno = 0x7ffffffd + offset;
		de.d_namlen = offset + 1;
		de.d_name[0] = '.';
		de.d_name[1] = '.';
		de.d_type = DT_DIR;
		dirent_terminate(&de);
		error = uiomove(&de, DE_SIZE, uio);
		if (error)
			goto out;
		offset++;
		uio->uio_offset += DE_SIZE;
	}
	if (limit == 0) {
		error = 0;
		goto out;
	}
	if (offset != np->n_dirofs || np->n_dirseq == NULL) {
		SMBVDEBUG("Reopening search %ld:%ld\n", offset, np->n_dirofs);
		if (np->n_dirseq) {
			smbfs_findclose(np->n_dirseq, scred);
			np->n_dirseq = NULL;
		}
		np->n_dirofs = 2;
		error = smbfs_findopen(np, "*", 1,
		    SMB_FA_SYSTEM | SMB_FA_HIDDEN | SMB_FA_DIR,
		    scred, &ctx);
		if (error) {
			SMBVDEBUG("can not open search, error = %d", error);
			goto out;
		}
		np->n_dirseq = ctx;
	} else
		ctx = np->n_dirseq;
	while (np->n_dirofs < offset) {
		error = smbfs_findnext(ctx, offset - np->n_dirofs++, scred);
		if (error) {
			smbfs_findclose(np->n_dirseq, scred);
			np->n_dirseq = NULL;
			error = ENOENT ? 0 : error;
			goto out;
		}
	}
	error = 0;
	for (; limit; limit--, offset++) {
		error = smbfs_findnext(ctx, limit, scred);
		if (error)
			break;
		np->n_dirofs++;
		bzero((caddr_t)&de, DE_SIZE);
		de.d_reclen = DE_SIZE;
		de.d_fileno = ctx->f_attr.fa_ino;
		de.d_type = (ctx->f_attr.fa_attr & SMB_FA_DIR) ? DT_DIR : DT_REG;
		de.d_namlen = ctx->f_nmlen;
		bcopy(ctx->f_name, de.d_name, de.d_namlen);
		dirent_terminate(&de);
		if (smbfs_fastlookup) {
			error = smbfs_nget(vp->v_mount, vp, ctx->f_name,
			    ctx->f_nmlen, &ctx->f_attr, &newvp);
			if (!error) {
				cn.cn_nameptr = de.d_name;
				cn.cn_namelen = de.d_namlen;
				cache_enter(vp, newvp, &cn);
				vput(newvp);
			}
		}
		error = uiomove(&de, DE_SIZE, uio);
		if (error)
			break;
	}
	if (error == ENOENT)
		error = 0;
	uio->uio_offset = offset * DE_SIZE;
out:
	smbfs_free_scred(scred);
	return error;
}