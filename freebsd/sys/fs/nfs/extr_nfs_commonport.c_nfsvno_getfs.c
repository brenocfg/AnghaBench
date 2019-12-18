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
struct TYPE_2__ {int tv_nsec; scalar_t__ tv_sec; } ;
struct nfsfsinfo {int fs_rtpref; int fs_wtpref; int fs_dtpref; int fs_maxfilesize; int fs_properties; TYPE_1__ fs_timedelta; void* fs_wtmult; void* fs_wtmax; void* fs_rtmult; void* fs_rtmax; } ;

/* Variables and functions */
 int NFSV3FSINFO_CANSETTIME ; 
 int NFSV3FSINFO_HOMOGENEOUS ; 
 int NFSV3FSINFO_LINK ; 
 int NFSV3FSINFO_SYMLINK ; 
 void* NFS_FABLKSIZE ; 
 int NFS_MAXDGRAMDATA ; 
 void* NFS_SRVMAXIO ; 

void
nfsvno_getfs(struct nfsfsinfo *sip, int isdgram)
{
	int pref;

	/*
	 * XXX
	 * There should be file system VFS OP(s) to get this information.
	 * For now, assume ufs.
	 */
	if (isdgram)
		pref = NFS_MAXDGRAMDATA;
	else
		pref = NFS_SRVMAXIO;
	sip->fs_rtmax = NFS_SRVMAXIO;
	sip->fs_rtpref = pref;
	sip->fs_rtmult = NFS_FABLKSIZE;
	sip->fs_wtmax = NFS_SRVMAXIO;
	sip->fs_wtpref = pref;
	sip->fs_wtmult = NFS_FABLKSIZE;
	sip->fs_dtpref = pref;
	sip->fs_maxfilesize = 0xffffffffffffffffull;
	sip->fs_timedelta.tv_sec = 0;
	sip->fs_timedelta.tv_nsec = 1;
	sip->fs_properties = (NFSV3FSINFO_LINK |
	    NFSV3FSINFO_SYMLINK | NFSV3FSINFO_HOMOGENEOUS |
	    NFSV3FSINFO_CANSETTIME);
}