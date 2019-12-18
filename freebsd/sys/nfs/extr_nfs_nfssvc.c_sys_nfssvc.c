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
struct thread {int dummy; } ;
struct nfssvc_args {int flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_CMD (int) ; 
 int EINTR ; 
 int EINVAL ; 
 int ERESTART ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int NFSSVC_ADDSOCK ; 
 int NFSSVC_ADMINREVOKE ; 
 int NFSSVC_BACKUPSTABLE ; 
 int NFSSVC_CBADDSOCK ; 
 int NFSSVC_DUMPCLIENTS ; 
 int NFSSVC_DUMPLOCKS ; 
 int NFSSVC_DUMPMNTOPTS ; 
 int NFSSVC_FORCEDISM ; 
 int NFSSVC_GETSTATS ; 
 int NFSSVC_GSSDADDFIRST ; 
 int NFSSVC_GSSDADDPORT ; 
 int NFSSVC_GSSDDELETEALL ; 
 int NFSSVC_IDNAME ; 
 int NFSSVC_NFSCBD ; 
 int NFSSVC_NFSD ; 
 int NFSSVC_NFSDADDSOCK ; 
 int NFSSVC_NFSDNFSD ; 
 int NFSSVC_NFSUSERDDELPORT ; 
 int NFSSVC_NFSUSERDPORT ; 
 int NFSSVC_NOPUBLICFH ; 
 int NFSSVC_OLDNFSD ; 
 int NFSSVC_PNFSDS ; 
 int NFSSVC_PUBLICFH ; 
 int NFSSVC_RESUMENFSD ; 
 int NFSSVC_STABLERESTART ; 
 int NFSSVC_SUSPENDNFSD ; 
 int NFSSVC_V4ROOTEXPORT ; 
 int /*<<< orphan*/  PRIV_NFS_DAEMON ; 
 int /*<<< orphan*/  mtx_owned (int /*<<< orphan*/ *) ; 
 int nfsd_call_nfscl (struct thread*,struct nfssvc_args*) ; 
 int nfsd_call_nfscommon (struct thread*,struct nfssvc_args*) ; 
 int nfsd_call_nfsd (struct thread*,struct nfssvc_args*) ; 
 int nfsd_call_nfsserver (struct thread*,struct nfssvc_args*) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int stub1 (struct thread*,struct nfssvc_args*) ; 
 int stub2 (struct thread*,struct nfssvc_args*) ; 
 int stub3 (struct thread*,struct nfssvc_args*) ; 
 int stub4 (struct thread*,struct nfssvc_args*) ; 

int
sys_nfssvc(struct thread *td, struct nfssvc_args *uap)
{
	int error;

	KASSERT(!mtx_owned(&Giant), ("nfssvc(): called with Giant"));

	AUDIT_ARG_CMD(uap->flag);

	/* Allow anyone to get the stats. */
	if ((uap->flag & ~NFSSVC_GETSTATS) != 0) {
		error = priv_check(td, PRIV_NFS_DAEMON);
		if (error != 0)
			return (error);
	}
	error = EINVAL;
	if ((uap->flag & (NFSSVC_ADDSOCK | NFSSVC_OLDNFSD | NFSSVC_NFSD)) &&
	    nfsd_call_nfsserver != NULL)
		error = (*nfsd_call_nfsserver)(td, uap);
	else if ((uap->flag & (NFSSVC_CBADDSOCK | NFSSVC_NFSCBD |
	    NFSSVC_DUMPMNTOPTS | NFSSVC_FORCEDISM)) && nfsd_call_nfscl != NULL)
		error = (*nfsd_call_nfscl)(td, uap);
	else if ((uap->flag & (NFSSVC_IDNAME | NFSSVC_GETSTATS |
	    NFSSVC_GSSDADDPORT | NFSSVC_GSSDADDFIRST | NFSSVC_GSSDDELETEALL |
	    NFSSVC_NFSUSERDPORT | NFSSVC_NFSUSERDDELPORT)) &&
	    nfsd_call_nfscommon != NULL)
		error = (*nfsd_call_nfscommon)(td, uap);
	else if ((uap->flag & (NFSSVC_NFSDNFSD | NFSSVC_NFSDADDSOCK |
	    NFSSVC_PUBLICFH | NFSSVC_V4ROOTEXPORT | NFSSVC_NOPUBLICFH |
	    NFSSVC_STABLERESTART | NFSSVC_ADMINREVOKE |
	    NFSSVC_DUMPCLIENTS | NFSSVC_DUMPLOCKS | NFSSVC_BACKUPSTABLE |
	    NFSSVC_SUSPENDNFSD | NFSSVC_RESUMENFSD | NFSSVC_PNFSDS)) &&
	    nfsd_call_nfsd != NULL)
		error = (*nfsd_call_nfsd)(td, uap);
	if (error == EINTR || error == ERESTART)
		error = 0;
	return (error);
}