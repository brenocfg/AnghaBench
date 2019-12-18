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
typedef  int /*<<< orphan*/  module_t ;
struct TYPE_2__ {int /*<<< orphan*/  nr_mtx; } ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  NFSEXITCODE (int) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newnfs_init () ; 
 int /*<<< orphan*/  newnfs_numnfsd ; 
 int /*<<< orphan*/  newnfs_portinit () ; 
 int /*<<< orphan*/  newnfsd_callout ; 
 int /*<<< orphan*/  newnfsd_mtx ; 
 int /*<<< orphan*/  nfs_clstate_mutex ; 
 int /*<<< orphan*/  nfs_nameid_mutex ; 
 int /*<<< orphan*/  nfs_numnfscbd ; 
 int /*<<< orphan*/  nfs_req_mutex ; 
 int /*<<< orphan*/  nfs_slock_mutex ; 
 int /*<<< orphan*/  nfs_sockl_mutex ; 
 int /*<<< orphan*/  nfs_state_mutex ; 
 int /*<<< orphan*/ * nfsd_call_nfscommon ; 
 int /*<<< orphan*/  nfsrv_cleanusergroup () ; 
 int /*<<< orphan*/  nfsrv_devidhead ; 
 int /*<<< orphan*/  nfsrv_dslock_mtx ; 
 int /*<<< orphan*/  nfsrv_nfsuserd ; 
 TYPE_1__ nfsrv_nfsuserdsock ; 
 int /*<<< orphan*/ * nfssvc_nfscommon ; 

__attribute__((used)) static int
nfscommon_modevent(module_t mod, int type, void *data)
{
	int error = 0;
	static int loaded = 0;

	switch (type) {
	case MOD_LOAD:
		if (loaded)
			goto out;
		newnfs_portinit();
		mtx_init(&nfs_nameid_mutex, "nfs_nameid_mutex", NULL, MTX_DEF);
		mtx_init(&nfs_sockl_mutex, "nfs_sockl_mutex", NULL, MTX_DEF);
		mtx_init(&nfs_slock_mutex, "nfs_slock_mutex", NULL, MTX_DEF);
		mtx_init(&nfs_req_mutex, "nfs_req_mutex", NULL, MTX_DEF);
		mtx_init(&nfsrv_nfsuserdsock.nr_mtx, "nfsuserd", NULL,
		    MTX_DEF);
		mtx_init(&nfsrv_dslock_mtx, "nfs4ds", NULL, MTX_DEF);
		TAILQ_INIT(&nfsrv_devidhead);
		callout_init(&newnfsd_callout, 1);
		newnfs_init();
		nfsd_call_nfscommon = nfssvc_nfscommon;
		loaded = 1;
		break;

	case MOD_UNLOAD:
		if (newnfs_numnfsd != 0 || nfsrv_nfsuserd != 0 ||
		    nfs_numnfscbd != 0) {
			error = EBUSY;
			break;
		}

		nfsd_call_nfscommon = NULL;
		callout_drain(&newnfsd_callout);
		/* Clean out the name<-->id cache. */
		nfsrv_cleanusergroup();
		/* and get rid of the mutexes */
		mtx_destroy(&nfs_nameid_mutex);
		mtx_destroy(&newnfsd_mtx);
		mtx_destroy(&nfs_state_mutex);
		mtx_destroy(&nfs_clstate_mutex);
		mtx_destroy(&nfs_sockl_mutex);
		mtx_destroy(&nfs_slock_mutex);
		mtx_destroy(&nfs_req_mutex);
		mtx_destroy(&nfsrv_nfsuserdsock.nr_mtx);
		mtx_destroy(&nfsrv_dslock_mtx);
		loaded = 0;
		break;
	default:
		error = EOPNOTSUPP;
		break;
	}

out:
	NFSEXITCODE(error);
	return error;
}