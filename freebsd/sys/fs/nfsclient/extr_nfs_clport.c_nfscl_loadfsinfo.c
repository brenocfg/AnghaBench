#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfsmount {int nm_wsize; int nm_rsize; int nm_readdirsize; scalar_t__ nm_maxfilesize; int /*<<< orphan*/  nm_state; TYPE_2__* nm_mountp; } ;
struct nfsfsinfo {int fs_wtpref; int fs_wtmax; int fs_rtpref; int fs_rtmax; int fs_dtpref; scalar_t__ fs_maxfilesize; } ;
struct TYPE_3__ {int /*<<< orphan*/  f_iosize; } ;
struct TYPE_4__ {TYPE_1__ mnt_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSSTA_GOTFSINFO ; 
 int NFS_DIRBLKSIZ ; 
 int NFS_FABLKSIZE ; 
 int /*<<< orphan*/  newnfs_iosize (struct nfsmount*) ; 

void
nfscl_loadfsinfo(struct nfsmount *nmp, struct nfsfsinfo *fsp)
{

	if ((nmp->nm_wsize == 0 || fsp->fs_wtpref < nmp->nm_wsize) &&
	    fsp->fs_wtpref >= NFS_FABLKSIZE)
		nmp->nm_wsize = (fsp->fs_wtpref + NFS_FABLKSIZE - 1) &
		    ~(NFS_FABLKSIZE - 1);
	if (fsp->fs_wtmax < nmp->nm_wsize && fsp->fs_wtmax > 0) {
		nmp->nm_wsize = fsp->fs_wtmax & ~(NFS_FABLKSIZE - 1);
		if (nmp->nm_wsize == 0)
			nmp->nm_wsize = fsp->fs_wtmax;
	}
	if (nmp->nm_wsize < NFS_FABLKSIZE)
		nmp->nm_wsize = NFS_FABLKSIZE;
	if ((nmp->nm_rsize == 0 || fsp->fs_rtpref < nmp->nm_rsize) &&
	    fsp->fs_rtpref >= NFS_FABLKSIZE)
		nmp->nm_rsize = (fsp->fs_rtpref + NFS_FABLKSIZE - 1) &
		    ~(NFS_FABLKSIZE - 1);
	if (fsp->fs_rtmax < nmp->nm_rsize && fsp->fs_rtmax > 0) {
		nmp->nm_rsize = fsp->fs_rtmax & ~(NFS_FABLKSIZE - 1);
		if (nmp->nm_rsize == 0)
			nmp->nm_rsize = fsp->fs_rtmax;
	}
	if (nmp->nm_rsize < NFS_FABLKSIZE)
		nmp->nm_rsize = NFS_FABLKSIZE;
	if ((nmp->nm_readdirsize == 0 || fsp->fs_dtpref < nmp->nm_readdirsize)
	    && fsp->fs_dtpref >= NFS_DIRBLKSIZ)
		nmp->nm_readdirsize = (fsp->fs_dtpref + NFS_DIRBLKSIZ - 1) &
		    ~(NFS_DIRBLKSIZ - 1);
	if (fsp->fs_rtmax < nmp->nm_readdirsize && fsp->fs_rtmax > 0) {
		nmp->nm_readdirsize = fsp->fs_rtmax & ~(NFS_DIRBLKSIZ - 1);
		if (nmp->nm_readdirsize == 0)
			nmp->nm_readdirsize = fsp->fs_rtmax;
	}
	if (nmp->nm_readdirsize < NFS_DIRBLKSIZ)
		nmp->nm_readdirsize = NFS_DIRBLKSIZ;
	if (fsp->fs_maxfilesize > 0 &&
	    fsp->fs_maxfilesize < nmp->nm_maxfilesize)
		nmp->nm_maxfilesize = fsp->fs_maxfilesize;
	nmp->nm_mountp->mnt_stat.f_iosize = newnfs_iosize(nmp);
	nmp->nm_state |= NFSSTA_GOTFSINFO;
}