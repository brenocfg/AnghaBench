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
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  NFSD_LOCK () ; 
 int /*<<< orphan*/  NFSD_UNLOCK () ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ncl_call_invalcaches ; 
 int /*<<< orphan*/ * ncl_invalcaches ; 
 int /*<<< orphan*/  ncl_iod_mutex ; 
 int /*<<< orphan*/  ncl_pbuf_zone ; 
 int /*<<< orphan*/  newnfs_portinit () ; 
 int /*<<< orphan*/  nfs_numnfscbd ; 
 int /*<<< orphan*/  nfscl_init () ; 
 int /*<<< orphan*/ * nfsd_call_nfscl ; 
 int /*<<< orphan*/  nfsrvd_cbinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfssvc_nfscl ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfscl_modevent(module_t mod, int type, void *data)
{
	int error = 0;
	static int loaded = 0;

	switch (type) {
	case MOD_LOAD:
		if (loaded)
			return (0);
		newnfs_portinit();
		mtx_init(&ncl_iod_mutex, "ncl_iod_mutex", NULL, MTX_DEF);
		nfscl_init();
		NFSD_LOCK();
		nfsrvd_cbinit(0);
		NFSD_UNLOCK();
		ncl_call_invalcaches = ncl_invalcaches;
		nfsd_call_nfscl = nfssvc_nfscl;
		loaded = 1;
		break;

	case MOD_UNLOAD:
		if (nfs_numnfscbd != 0) {
			error = EBUSY;
			break;
		}

		/*
		 * XXX: Unloading of nfscl module is unsupported.
		 */
#if 0
		ncl_call_invalcaches = NULL;
		nfsd_call_nfscl = NULL;
		uma_zdestroy(ncl_pbuf_zone);
		/* and get rid of the mutexes */
		mtx_destroy(&ncl_iod_mutex);
		loaded = 0;
		break;
#else
		/* FALLTHROUGH */
#endif
	default:
		error = EOPNOTSUPP;
		break;
	}
	return error;
}