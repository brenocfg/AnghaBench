#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct thread {struct proc* td_proc; } ;
struct proc {int /*<<< orphan*/  p_flag2; } ;
struct nfsd_nfsd_args {int /*<<< orphan*/  maxthreads; int /*<<< orphan*/  minthreads; int /*<<< orphan*/  principal; } ;
typedef  int /*<<< orphan*/  principal ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_5__ {int modifyfs; } ;
struct TYPE_4__ {int /*<<< orphan*/  sp_maxthreads; int /*<<< orphan*/  sp_minthreads; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_C_INDEFINITE ; 
 int /*<<< orphan*/  MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  NFSD_LOCK () ; 
 int /*<<< orphan*/  NFSD_UNLOCK () ; 
 int /*<<< orphan*/  NFSEXITCODE (int) ; 
 size_t NFSPROC_GETATTR ; 
 size_t NFSV4OP_GETATTR ; 
 int /*<<< orphan*/  NFS_PROG ; 
 int /*<<< orphan*/  NFS_VER2 ; 
 int /*<<< orphan*/  NFS_VER3 ; 
 int /*<<< orphan*/  NFS_VER4 ; 
 int /*<<< orphan*/  P2_AST_SU ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int copyinstr (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ newnfs_numnfsd ; 
 int /*<<< orphan*/  nfsdev_time ; 
 int nfsrv_createdevids (struct nfsd_nfsd_args*,struct thread*) ; 
 scalar_t__ nfsrv_devidcnt ; 
 int* nfsrv_writerpc ; 
 int /*<<< orphan*/  nfsrvd_init (int) ; 
 TYPE_1__* nfsrvd_pool ; 
 TYPE_2__* nfsv4_opflag ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rpc_gss_clear_svc_name_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_gss_set_svc_name_call (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_run (TYPE_1__*) ; 
 int /*<<< orphan*/  time_second ; 

int
nfsrvd_nfsd(struct thread *td, struct nfsd_nfsd_args *args)
{
	char principal[MAXHOSTNAMELEN + 5];
	struct proc *p;
	int error = 0;
	bool_t ret2, ret3, ret4;

	error = copyinstr(args->principal, principal, sizeof (principal),
	    NULL);
	if (error)
		goto out;

	/*
	 * Only the first nfsd actually does any work. The RPC code
	 * adds threads to it as needed. Any extra processes offered
	 * by nfsd just exit. If nfsd is new enough, it will call us
	 * once with a structure that specifies how many threads to
	 * use.
	 */
	NFSD_LOCK();
	if (newnfs_numnfsd == 0) {
		nfsdev_time = time_second;
		p = td->td_proc;
		PROC_LOCK(p);
		p->p_flag2 |= P2_AST_SU;
		PROC_UNLOCK(p);
		newnfs_numnfsd++;

		NFSD_UNLOCK();
		error = nfsrv_createdevids(args, td);
		if (error == 0) {
			/* An empty string implies AUTH_SYS only. */
			if (principal[0] != '\0') {
				ret2 = rpc_gss_set_svc_name_call(principal,
				    "kerberosv5", GSS_C_INDEFINITE, NFS_PROG,
				    NFS_VER2);
				ret3 = rpc_gss_set_svc_name_call(principal,
				    "kerberosv5", GSS_C_INDEFINITE, NFS_PROG,
				    NFS_VER3);
				ret4 = rpc_gss_set_svc_name_call(principal,
				    "kerberosv5", GSS_C_INDEFINITE, NFS_PROG,
				    NFS_VER4);
	
				if (!ret2 || !ret3 || !ret4)
					printf(
					    "nfsd: can't register svc name\n");
			}
	
			nfsrvd_pool->sp_minthreads = args->minthreads;
			nfsrvd_pool->sp_maxthreads = args->maxthreads;
				
			/*
			 * If this is a pNFS service, make Getattr do a
			 * vn_start_write(), so it can do a vn_set_extattr().
			 */
			if (nfsrv_devidcnt > 0) {
				nfsrv_writerpc[NFSPROC_GETATTR] = 1;
				nfsv4_opflag[NFSV4OP_GETATTR].modifyfs = 1;
			}

			svc_run(nfsrvd_pool);
	
			/* Reset Getattr to not do a vn_start_write(). */
			nfsrv_writerpc[NFSPROC_GETATTR] = 0;
			nfsv4_opflag[NFSV4OP_GETATTR].modifyfs = 0;

			if (principal[0] != '\0') {
				rpc_gss_clear_svc_name_call(NFS_PROG, NFS_VER2);
				rpc_gss_clear_svc_name_call(NFS_PROG, NFS_VER3);
				rpc_gss_clear_svc_name_call(NFS_PROG, NFS_VER4);
			}
		}
		NFSD_LOCK();
		newnfs_numnfsd--;
		nfsrvd_init(1);
		PROC_LOCK(p);
		p->p_flag2 &= ~P2_AST_SU;
		PROC_UNLOCK(p);
	}
	NFSD_UNLOCK();

out:
	NFSEXITCODE(error);
	return (error);
}