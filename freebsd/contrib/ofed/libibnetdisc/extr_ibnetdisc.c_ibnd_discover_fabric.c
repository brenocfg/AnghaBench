#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_14__ ;

/* Type definitions */
struct ibnd_config {int /*<<< orphan*/  mkey; int /*<<< orphan*/  retries; int /*<<< orphan*/  timeout_ms; int /*<<< orphan*/  member_0; } ;
struct ibmad_port {int dummy; } ;
struct TYPE_20__ {int /*<<< orphan*/  total_smps; } ;
typedef  TYPE_2__ smp_engine_t ;
struct TYPE_21__ {scalar_t__ initial_hops; int /*<<< orphan*/  selfportid; struct ibnd_config* cfg; TYPE_5__* f_int; } ;
typedef  TYPE_3__ ibnd_scan_t ;
typedef  int /*<<< orphan*/  ibnd_fabric_t ;
struct TYPE_19__ {scalar_t__ cnt; } ;
struct TYPE_22__ {TYPE_1__ drpath; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ ib_portid_t ;
struct TYPE_18__ {int /*<<< orphan*/  maxhops_discovered; int /*<<< orphan*/  total_mads_used; } ;
struct TYPE_23__ {TYPE_14__ fabric; } ;
typedef  TYPE_5__ f_internal_t ;

/* Variables and functions */
 int /*<<< orphan*/  IBND_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBND_ERROR (char*,...) ; 
 int IB_SMI_CLASS ; 
 int IB_SMI_DIRECT_CLASS ; 
 TYPE_5__* allocate_fabric_internal () ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 scalar_t__ group_nodes (TYPE_14__*) ; 
 scalar_t__ ib_resolve_self_via (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ibmad_port*) ; 
 int /*<<< orphan*/  ibnd_destroy_fabric (TYPE_14__*) ; 
 int /*<<< orphan*/  mad_rpc_close_port (struct ibmad_port*) ; 
 struct ibmad_port* mad_rpc_open_port (char*,int,int*,int) ; 
 int /*<<< orphan*/  mad_rpc_set_retries (struct ibmad_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mad_rpc_set_timeout (struct ibmad_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  portid2str (TYPE_4__*) ; 
 scalar_t__ process_mads (TYPE_2__*) ; 
 int /*<<< orphan*/  query_node_info (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ set_config (struct ibnd_config*,struct ibnd_config*) ; 
 int /*<<< orphan*/  smp_engine_destroy (TYPE_2__*) ; 
 scalar_t__ smp_engine_init (TYPE_2__*,char*,int,TYPE_3__*,struct ibnd_config*) ; 
 int /*<<< orphan*/  smp_mkey_set (struct ibmad_port*,int /*<<< orphan*/ ) ; 

ibnd_fabric_t *ibnd_discover_fabric(char * ca_name, int ca_port,
				    ib_portid_t * from,
				    struct ibnd_config *cfg)
{
	struct ibnd_config config = { 0 };
	f_internal_t *f_int = NULL;
	ib_portid_t my_portid = { 0 };
	smp_engine_t engine;
	ibnd_scan_t scan;
	struct ibmad_port *ibmad_port;
	int nc = 2;
	int mc[2] = { IB_SMI_CLASS, IB_SMI_DIRECT_CLASS };

	/* If not specified start from "my" port */
	if (!from)
		from = &my_portid;

	if (set_config(&config, cfg)) {
		IBND_ERROR("Invalid ibnd_config\n");
		return NULL;
	}

	f_int = allocate_fabric_internal();
	if (!f_int) {
		IBND_ERROR("OOM: failed to calloc ibnd_fabric_t\n");
		return NULL;
	}

	memset(&scan.selfportid, 0, sizeof(scan.selfportid));
	scan.f_int = f_int;
	scan.cfg = &config;
	scan.initial_hops = from->drpath.cnt;

	ibmad_port = mad_rpc_open_port(ca_name, ca_port, mc, nc);
	if (!ibmad_port) {
		IBND_ERROR("can't open MAD port (%s:%d)\n", ca_name, ca_port);
		return (NULL);
	}
	mad_rpc_set_timeout(ibmad_port, cfg->timeout_ms);
	mad_rpc_set_retries(ibmad_port, cfg->retries);
	smp_mkey_set(ibmad_port, cfg->mkey);

	if (ib_resolve_self_via(&scan.selfportid,
				NULL, NULL, ibmad_port) < 0) {
		IBND_ERROR("Failed to resolve self\n");
		mad_rpc_close_port(ibmad_port);
		return NULL;
	}
	mad_rpc_close_port(ibmad_port);

	if (smp_engine_init(&engine, ca_name, ca_port, &scan, &config)) {
		free(f_int);
		return (NULL);
	}

	IBND_DEBUG("from %s\n", portid2str(from));

	if (!query_node_info(&engine, from, NULL))
		if (process_mads(&engine) != 0)
			goto error;

	f_int->fabric.total_mads_used = engine.total_smps;
	f_int->fabric.maxhops_discovered += scan.initial_hops;

	if (group_nodes(&f_int->fabric))
		goto error;

	smp_engine_destroy(&engine);
	return (ibnd_fabric_t *)f_int;
error:
	smp_engine_destroy(&engine);
	ibnd_destroy_fabric(&f_int->fabric);
	return NULL;
}