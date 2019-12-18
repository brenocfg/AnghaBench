#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct nfsd_nfscbd_args {int /*<<< orphan*/  principal; } ;
typedef  int /*<<< orphan*/  principal ;
struct TYPE_3__ {int sp_minthreads; int sp_maxthreads; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_C_INDEFINITE ; 
 int /*<<< orphan*/  NFSD_LOCK () ; 
 int /*<<< orphan*/  NFSD_UNLOCK () ; 
 int /*<<< orphan*/  NFSV4_CBVERS ; 
 int /*<<< orphan*/  NFS_CALLBCKPROG ; 
 int copyinstr (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ nfs_numnfscbd ; 
 TYPE_1__* nfscbd_pool ; 
 int /*<<< orphan*/  nfsrvd_cbinit (int) ; 
 int /*<<< orphan*/  rpc_gss_clear_svc_name_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_gss_set_svc_name_call (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_run (TYPE_1__*) ; 

int
nfscbd_nfsd(struct thread *td, struct nfsd_nfscbd_args *args)
{
	char principal[128];
	int error;

	if (args != NULL) {
		error = copyinstr(args->principal, principal,
		    sizeof(principal), NULL);
		if (error)
			return (error);
	} else {
		principal[0] = '\0';
	}

	/*
	 * Only the first nfsd actually does any work. The RPC code
	 * adds threads to it as needed. Any extra processes offered
	 * by nfsd just exit. If nfsd is new enough, it will call us
	 * once with a structure that specifies how many threads to
	 * use.
	 */
	NFSD_LOCK();
	if (nfs_numnfscbd == 0) {
		nfs_numnfscbd++;

		NFSD_UNLOCK();

		if (principal[0] != '\0')
			rpc_gss_set_svc_name_call(principal, "kerberosv5",
			    GSS_C_INDEFINITE, NFS_CALLBCKPROG, NFSV4_CBVERS);

		nfscbd_pool->sp_minthreads = 4;
		nfscbd_pool->sp_maxthreads = 4;
			
		svc_run(nfscbd_pool);

		rpc_gss_clear_svc_name_call(NFS_CALLBCKPROG, NFSV4_CBVERS);

		NFSD_LOCK();
		nfs_numnfscbd--;
		nfsrvd_cbinit(1);
	}
	NFSD_UNLOCK();

	return (0);
}