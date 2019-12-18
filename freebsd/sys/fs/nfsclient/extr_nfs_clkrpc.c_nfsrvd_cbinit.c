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
struct TYPE_4__ {int /*<<< orphan*/ * sp_done; int /*<<< orphan*/ * sp_assign; int /*<<< orphan*/ * sp_rcache; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSDLOCKMUTEXPTR ; 
 int /*<<< orphan*/  NFSD_LOCK () ; 
 int /*<<< orphan*/  NFSD_LOCK_ASSERT () ; 
 int /*<<< orphan*/  NFSD_UNLOCK () ; 
 int /*<<< orphan*/  PZERO ; 
 int /*<<< orphan*/  msleep (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_numnfscbd ; 
 TYPE_1__* nfscbd_pool ; 
 int /*<<< orphan*/  svcpool_close (TYPE_1__*) ; 
 TYPE_1__* svcpool_create (char*,int /*<<< orphan*/ *) ; 

void
nfsrvd_cbinit(int terminating)
{

	NFSD_LOCK_ASSERT();

	if (terminating) {
		/* Wait for any xprt registrations to complete. */
		while (nfs_numnfscbd > 0)
			msleep(&nfs_numnfscbd, NFSDLOCKMUTEXPTR, PZERO, 
			    "nfscbdt", 0);
		if (nfscbd_pool != NULL) {
			NFSD_UNLOCK();
			svcpool_close(nfscbd_pool);
			NFSD_LOCK();
		}
	}

	if (nfscbd_pool == NULL) {
		NFSD_UNLOCK();
		nfscbd_pool = svcpool_create("nfscbd", NULL);
		nfscbd_pool->sp_rcache = NULL;
		nfscbd_pool->sp_assign = NULL;
		nfscbd_pool->sp_done = NULL;
		NFSD_LOCK();
	}
}