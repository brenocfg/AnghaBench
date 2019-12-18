#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sp_done; int /*<<< orphan*/  sp_assign; int /*<<< orphan*/ * sp_rcache; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  NFSD_LOCK () ; 
 int /*<<< orphan*/  NFSD_LOCK_ASSERT () ; 
 int /*<<< orphan*/  NFSD_UNLOCK () ; 
 int /*<<< orphan*/  SYSCTL_STATIC_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _vfs_nfsd ; 
 int /*<<< orphan*/  fha_nd_complete ; 
 int /*<<< orphan*/  fhanew_assign ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfsd_master_proc ; 
 int /*<<< orphan*/  nfsrv_freeallbackchannel_xprts () ; 
 int /*<<< orphan*/  nfsrv_freealllayoutsanddevids () ; 
 int /*<<< orphan*/ * nfsrv_zeropnfsdat ; 
 TYPE_1__* nfsrvd_pool ; 
 int /*<<< orphan*/  svcpool_close (TYPE_1__*) ; 
 TYPE_1__* svcpool_create (char*,int /*<<< orphan*/ ) ; 

void
nfsrvd_init(int terminating)
{

	NFSD_LOCK_ASSERT();

	if (terminating) {
		nfsd_master_proc = NULL;
		NFSD_UNLOCK();
		nfsrv_freealllayoutsanddevids();
		nfsrv_freeallbackchannel_xprts();
		svcpool_close(nfsrvd_pool);
		free(nfsrv_zeropnfsdat, M_TEMP);
		nfsrv_zeropnfsdat = NULL;
		NFSD_LOCK();
	} else {
		NFSD_UNLOCK();
		nfsrvd_pool = svcpool_create("nfsd",
		    SYSCTL_STATIC_CHILDREN(_vfs_nfsd));
		nfsrvd_pool->sp_rcache = NULL;
		nfsrvd_pool->sp_assign = fhanew_assign;
		nfsrvd_pool->sp_done = fha_nd_complete;
		NFSD_LOCK();
	}
}