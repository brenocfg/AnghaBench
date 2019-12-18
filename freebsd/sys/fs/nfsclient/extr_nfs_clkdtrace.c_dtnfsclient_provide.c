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
typedef  int /*<<< orphan*/  dtrace_probedesc_t ;
struct TYPE_2__ {int /*<<< orphan*/ * nr_v4_name; void* nr_v4_id_done; void* nr_v4_id_start; int /*<<< orphan*/ * nr_v3_name; void* nr_v3_id_done; void* nr_v3_id_start; int /*<<< orphan*/ * nr_v2_name; void* nr_v2_id_done; void* nr_v2_id_start; } ;

/* Variables and functions */
 int NFSV41_NPROCS ; 
 int /*<<< orphan*/  dtnfsclient_accesscache_str ; 
 int /*<<< orphan*/  dtnfsclient_attrcache_str ; 
 int /*<<< orphan*/  dtnfsclient_done_str ; 
 int /*<<< orphan*/ * dtnfsclient_flush_str ; 
 int /*<<< orphan*/ * dtnfsclient_get_str ; 
 int /*<<< orphan*/  dtnfsclient_hit_str ; 
 int /*<<< orphan*/  dtnfsclient_id ; 
 int /*<<< orphan*/ * dtnfsclient_load_str ; 
 int /*<<< orphan*/  dtnfsclient_miss_str ; 
 int /*<<< orphan*/  dtnfsclient_nfs2_str ; 
 int /*<<< orphan*/  dtnfsclient_nfs3_str ; 
 int /*<<< orphan*/  dtnfsclient_nfs4_str ; 
 TYPE_1__* dtnfsclient_rpcs ; 
 int /*<<< orphan*/  dtnfsclient_start_str ; 
 void* dtrace_probe_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ dtrace_probe_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* nfscl_accesscache_flush_done_id ; 
 void* nfscl_accesscache_get_hit_id ; 
 void* nfscl_accesscache_get_miss_id ; 
 void* nfscl_accesscache_load_done_id ; 
 void* nfscl_attrcache_flush_done_id ; 
 void* nfscl_attrcache_get_hit_id ; 
 void* nfscl_attrcache_get_miss_id ; 
 void* nfscl_attrcache_load_done_id ; 
 int /*<<< orphan*/ * nfscl_nfs2_done_probes ; 
 int /*<<< orphan*/ * nfscl_nfs2_start_probes ; 
 int /*<<< orphan*/ * nfscl_nfs3_done_probes ; 
 int /*<<< orphan*/ * nfscl_nfs3_start_probes ; 
 int /*<<< orphan*/ * nfscl_nfs4_done_probes ; 
 int /*<<< orphan*/ * nfscl_nfs4_start_probes ; 

__attribute__((used)) static void
dtnfsclient_provide(void *arg, dtrace_probedesc_t *desc)
{
	int i;

	if (desc != NULL)
		return;

	/*
	 * Register access cache probes.
	 */
	if (dtrace_probe_lookup(dtnfsclient_id, dtnfsclient_accesscache_str,
	    dtnfsclient_flush_str, dtnfsclient_done_str) == 0) {
		nfscl_accesscache_flush_done_id = dtrace_probe_create(
		    dtnfsclient_id, dtnfsclient_accesscache_str,
		    dtnfsclient_flush_str, dtnfsclient_done_str, 0, NULL);
	}
	if (dtrace_probe_lookup(dtnfsclient_id, dtnfsclient_accesscache_str,
	    dtnfsclient_get_str, dtnfsclient_hit_str) == 0) {
		nfscl_accesscache_get_hit_id = dtrace_probe_create(
		    dtnfsclient_id, dtnfsclient_accesscache_str,
		    dtnfsclient_get_str, dtnfsclient_hit_str, 0, NULL);
	}
	if (dtrace_probe_lookup(dtnfsclient_id, dtnfsclient_accesscache_str,
	    dtnfsclient_get_str, dtnfsclient_miss_str) == 0) {
		nfscl_accesscache_get_miss_id = dtrace_probe_create(
		    dtnfsclient_id, dtnfsclient_accesscache_str,
		    dtnfsclient_get_str, dtnfsclient_miss_str, 0, NULL);
	}
	if (dtrace_probe_lookup(dtnfsclient_id, dtnfsclient_accesscache_str,
	    dtnfsclient_load_str, dtnfsclient_done_str) == 0) {
		nfscl_accesscache_load_done_id = dtrace_probe_create(
		    dtnfsclient_id, dtnfsclient_accesscache_str,
		    dtnfsclient_load_str, dtnfsclient_done_str, 0, NULL);
	}

	/*
	 * Register attribute cache probes.
	 */
	if (dtrace_probe_lookup(dtnfsclient_id, dtnfsclient_attrcache_str,
	    dtnfsclient_flush_str, dtnfsclient_done_str) == 0) {
		nfscl_attrcache_flush_done_id = dtrace_probe_create(
		    dtnfsclient_id, dtnfsclient_attrcache_str,
		    dtnfsclient_flush_str, dtnfsclient_done_str, 0, NULL);
	}
	if (dtrace_probe_lookup(dtnfsclient_id, dtnfsclient_attrcache_str,
	    dtnfsclient_get_str, dtnfsclient_hit_str) == 0) {
		nfscl_attrcache_get_hit_id = dtrace_probe_create(
		    dtnfsclient_id, dtnfsclient_attrcache_str,
		    dtnfsclient_get_str, dtnfsclient_hit_str, 0, NULL);
	}
	if (dtrace_probe_lookup(dtnfsclient_id, dtnfsclient_attrcache_str,
	    dtnfsclient_get_str, dtnfsclient_miss_str) == 0) {
		nfscl_attrcache_get_miss_id = dtrace_probe_create(
		    dtnfsclient_id, dtnfsclient_attrcache_str,
		    dtnfsclient_get_str, dtnfsclient_miss_str, 0, NULL);
	}
	if (dtrace_probe_lookup(dtnfsclient_id, dtnfsclient_attrcache_str,
	    dtnfsclient_load_str, dtnfsclient_done_str) == 0) {
		nfscl_attrcache_load_done_id = dtrace_probe_create(
		    dtnfsclient_id, dtnfsclient_attrcache_str,
		    dtnfsclient_load_str, dtnfsclient_done_str, 0, NULL);
	}

	/*
	 * Register NFSv2 RPC procedures; note sparseness check for each slot
	 * in the NFSv3, NFSv4 procnum-indexed array.
	 */
	for (i = 0; i < NFSV41_NPROCS + 1; i++) {
		if (dtnfsclient_rpcs[i].nr_v2_name != NULL &&
		    dtrace_probe_lookup(dtnfsclient_id, dtnfsclient_nfs2_str,
		    dtnfsclient_rpcs[i].nr_v2_name, dtnfsclient_start_str) ==
		    0) {
			dtnfsclient_rpcs[i].nr_v2_id_start =
			    dtrace_probe_create(dtnfsclient_id,
			    dtnfsclient_nfs2_str,
			    dtnfsclient_rpcs[i].nr_v2_name,
			    dtnfsclient_start_str, 0,
			    &nfscl_nfs2_start_probes[i]);
		}
		if (dtnfsclient_rpcs[i].nr_v2_name != NULL &&
		    dtrace_probe_lookup(dtnfsclient_id, dtnfsclient_nfs2_str,
		    dtnfsclient_rpcs[i].nr_v2_name, dtnfsclient_done_str) ==
		    0) {
			dtnfsclient_rpcs[i].nr_v2_id_done = 
			    dtrace_probe_create(dtnfsclient_id,
			    dtnfsclient_nfs2_str,
			    dtnfsclient_rpcs[i].nr_v2_name,
			    dtnfsclient_done_str, 0,
			    &nfscl_nfs2_done_probes[i]);
		}
	}

	/*
	 * Register NFSv3 RPC procedures; note sparseness check for each slot
	 * in the NFSv4 procnum-indexed array.
	 */
	for (i = 0; i < NFSV41_NPROCS + 1; i++) {
		if (dtnfsclient_rpcs[i].nr_v3_name != NULL &&
		    dtrace_probe_lookup(dtnfsclient_id, dtnfsclient_nfs3_str,
		    dtnfsclient_rpcs[i].nr_v3_name, dtnfsclient_start_str) ==
		    0) {
			dtnfsclient_rpcs[i].nr_v3_id_start =
			    dtrace_probe_create(dtnfsclient_id,
			    dtnfsclient_nfs3_str,
			    dtnfsclient_rpcs[i].nr_v3_name,
			    dtnfsclient_start_str, 0,
			    &nfscl_nfs3_start_probes[i]);
		}
		if (dtnfsclient_rpcs[i].nr_v3_name != NULL &&
		    dtrace_probe_lookup(dtnfsclient_id, dtnfsclient_nfs3_str,
		    dtnfsclient_rpcs[i].nr_v3_name, dtnfsclient_done_str) ==
		    0) {
			dtnfsclient_rpcs[i].nr_v3_id_done = 
			    dtrace_probe_create(dtnfsclient_id,
			    dtnfsclient_nfs3_str,
			    dtnfsclient_rpcs[i].nr_v3_name,
			    dtnfsclient_done_str, 0,
			    &nfscl_nfs3_done_probes[i]);
		}
	}

	/*
	 * Register NFSv4 RPC procedures.
	 */
	for (i = 0; i < NFSV41_NPROCS + 1; i++) {
		if (dtrace_probe_lookup(dtnfsclient_id, dtnfsclient_nfs4_str,
		    dtnfsclient_rpcs[i].nr_v4_name, dtnfsclient_start_str) ==
		    0) {
			dtnfsclient_rpcs[i].nr_v4_id_start =
			    dtrace_probe_create(dtnfsclient_id,
			    dtnfsclient_nfs4_str,
			    dtnfsclient_rpcs[i].nr_v4_name,
			    dtnfsclient_start_str, 0,
			    &nfscl_nfs4_start_probes[i]);
		}
		if (dtrace_probe_lookup(dtnfsclient_id, dtnfsclient_nfs4_str,
		    dtnfsclient_rpcs[i].nr_v4_name, dtnfsclient_done_str) ==
		    0) {
			dtnfsclient_rpcs[i].nr_v4_id_done = 
			    dtrace_probe_create(dtnfsclient_id,
			    dtnfsclient_nfs4_str,
			    dtnfsclient_rpcs[i].nr_v4_name,
			    dtnfsclient_done_str, 0,
			    &nfscl_nfs4_done_probes[i]);
		}
	}
}