#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  module_t ;
struct TYPE_14__ {int /*<<< orphan*/  mtx; } ;
struct TYPE_13__ {int /*<<< orphan*/  mtx; } ;
struct TYPE_12__ {int /*<<< orphan*/  mtx; } ;
struct TYPE_11__ {int /*<<< orphan*/  mnt_explock; int /*<<< orphan*/  mnt_mtx; } ;
struct TYPE_10__ {int /*<<< orphan*/ * vndeleg_disable; int /*<<< orphan*/ * vndeleg_recall; } ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_NFSDCLIENT ; 
 int /*<<< orphan*/  M_NFSDLOCKFILE ; 
 int /*<<< orphan*/  M_NFSDSESSION ; 
 int /*<<< orphan*/  NFSD_LOCK () ; 
 int /*<<< orphan*/  NFSD_UNLOCK () ; 
 int /*<<< orphan*/  NFSEXITCODE (int) ; 
 int NFSRVCACHE_HASHSIZE ; 
 int /*<<< orphan*/  PVFS ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  free (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockinit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newnfs_numnfsd ; 
 int /*<<< orphan*/  newnfs_portinit () ; 
 int /*<<< orphan*/  nfs_v4root_mutex ; 
 TYPE_3__* nfsclienthash ; 
 int /*<<< orphan*/ * nfsd_call_nfsd ; 
 int /*<<< orphan*/ * nfsd_call_servertimer ; 
 int /*<<< orphan*/ * nfsd_disabledelegation ; 
 int /*<<< orphan*/  nfsd_init () ; 
 int /*<<< orphan*/  nfsd_mntinit () ; 
 int /*<<< orphan*/ * nfsd_recalldelegation ; 
 TYPE_3__* nfslayouthash ; 
 TYPE_3__* nfslockhash ; 
 int /*<<< orphan*/  nfsrc_udpmtx ; 
 TYPE_5__* nfsrcahash_table ; 
 TYPE_4__* nfsrchash_table ; 
 int /*<<< orphan*/  nfsrv_dontlistlock_mtx ; 
 int nfsrv_layouthashsize ; 
 int /*<<< orphan*/  nfsrv_recalllock_mtx ; 
 int /*<<< orphan*/ * nfsrv_servertimer ; 
 int nfsrv_sessionhashsize ; 
 int /*<<< orphan*/  nfsrv_throwawayallstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsrvd_cleancache () ; 
 int /*<<< orphan*/  nfsrvd_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsrvd_initcache () ; 
 int /*<<< orphan*/ * nfsrvd_pool ; 
 TYPE_3__* nfssessionhash ; 
 int /*<<< orphan*/ * nfssvc_nfsd ; 
 TYPE_2__ nfsv4root_mnt ; 
 int /*<<< orphan*/  svcpool_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__ vn_deleg_ops ; 

__attribute__((used)) static int
nfsd_modevent(module_t mod, int type, void *data)
{
	int error = 0, i;
	static int loaded = 0;

	switch (type) {
	case MOD_LOAD:
		if (loaded)
			goto out;
		newnfs_portinit();
		for (i = 0; i < NFSRVCACHE_HASHSIZE; i++) {
			mtx_init(&nfsrchash_table[i].mtx, "nfsrtc", NULL,
			    MTX_DEF);
			mtx_init(&nfsrcahash_table[i].mtx, "nfsrtca", NULL,
			    MTX_DEF);
		}
		mtx_init(&nfsrc_udpmtx, "nfsuc", NULL, MTX_DEF);
		mtx_init(&nfs_v4root_mutex, "nfs4rt", NULL, MTX_DEF);
		mtx_init(&nfsv4root_mnt.mnt_mtx, "nfs4mnt", NULL, MTX_DEF);
		mtx_init(&nfsrv_dontlistlock_mtx, "nfs4dnl", NULL, MTX_DEF);
		mtx_init(&nfsrv_recalllock_mtx, "nfs4rec", NULL, MTX_DEF);
		lockinit(&nfsv4root_mnt.mnt_explock, PVFS, "explock", 0, 0);
		nfsrvd_initcache();
		nfsd_init();
		NFSD_LOCK();
		nfsrvd_init(0);
		NFSD_UNLOCK();
		nfsd_mntinit();
#ifdef VV_DISABLEDELEG
		vn_deleg_ops.vndeleg_recall = nfsd_recalldelegation;
		vn_deleg_ops.vndeleg_disable = nfsd_disabledelegation;
#endif
		nfsd_call_servertimer = nfsrv_servertimer;
		nfsd_call_nfsd = nfssvc_nfsd;
		loaded = 1;
		break;

	case MOD_UNLOAD:
		if (newnfs_numnfsd != 0) {
			error = EBUSY;
			break;
		}

#ifdef VV_DISABLEDELEG
		vn_deleg_ops.vndeleg_recall = NULL;
		vn_deleg_ops.vndeleg_disable = NULL;
#endif
		nfsd_call_servertimer = NULL;
		nfsd_call_nfsd = NULL;

		/* Clean out all NFSv4 state. */
		nfsrv_throwawayallstate(curthread);

		/* Clean the NFS server reply cache */
		nfsrvd_cleancache();

		/* Free up the krpc server pool. */
		if (nfsrvd_pool != NULL)
			svcpool_destroy(nfsrvd_pool);

		/* and get rid of the locks */
		for (i = 0; i < NFSRVCACHE_HASHSIZE; i++) {
			mtx_destroy(&nfsrchash_table[i].mtx);
			mtx_destroy(&nfsrcahash_table[i].mtx);
		}
		mtx_destroy(&nfsrc_udpmtx);
		mtx_destroy(&nfs_v4root_mutex);
		mtx_destroy(&nfsv4root_mnt.mnt_mtx);
		mtx_destroy(&nfsrv_dontlistlock_mtx);
		mtx_destroy(&nfsrv_recalllock_mtx);
		for (i = 0; i < nfsrv_sessionhashsize; i++)
			mtx_destroy(&nfssessionhash[i].mtx);
		if (nfslayouthash != NULL) {
			for (i = 0; i < nfsrv_layouthashsize; i++)
				mtx_destroy(&nfslayouthash[i].mtx);
			free(nfslayouthash, M_NFSDSESSION);
		}
		lockdestroy(&nfsv4root_mnt.mnt_explock);
		free(nfsclienthash, M_NFSDCLIENT);
		free(nfslockhash, M_NFSDLOCKFILE);
		free(nfssessionhash, M_NFSDSESSION);
		loaded = 0;
		break;
	default:
		error = EOPNOTSUPP;
		break;
	}

out:
	NFSEXITCODE(error);
	return (error);
}