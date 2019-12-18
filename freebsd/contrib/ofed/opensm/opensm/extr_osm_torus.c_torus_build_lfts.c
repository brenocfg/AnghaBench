#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fabric {scalar_t__ ca_cnt; scalar_t__ switch_cnt; scalar_t__ link_cnt; TYPE_2__* osm; } ;
struct torus_context {struct torus* torus; TYPE_2__* osm; struct fabric fabric; } ;
struct torus {int flags; TYPE_2__* osm; scalar_t__ ca_cnt; scalar_t__ switch_cnt; scalar_t__ link_cnt; scalar_t__ z_sz; scalar_t__ y_sz; scalar_t__ x_sz; } ;
struct TYPE_6__ {int /*<<< orphan*/  qos_options; int /*<<< orphan*/  qos_rtr_options; int /*<<< orphan*/  qos_sw0_options; int /*<<< orphan*/  qos_ca_options; int /*<<< orphan*/  qos_swe_options; int /*<<< orphan*/  torus_conf_file; int /*<<< orphan*/  qos; } ;
typedef  TYPE_3__ osm_subn_opt_t ;
typedef  int /*<<< orphan*/  osm_log_t ;
struct TYPE_4__ {TYPE_3__ opt; scalar_t__ min_sw_data_vls; scalar_t__ min_data_vls; } ;
struct TYPE_5__ {int /*<<< orphan*/  log; TYPE_1__ subn; } ;

/* Variables and functions */
 scalar_t__ ALL_MESH (int) ; 
 int NOTIFY_CHANGES ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 int /*<<< orphan*/  OSM_LOG_INFO ; 
 int /*<<< orphan*/  build_torus (struct fabric*,struct torus*) ; 
 struct torus* calloc (int,int) ; 
 int /*<<< orphan*/  capture_fabric (struct fabric*) ; 
 int /*<<< orphan*/  check_qos_ep_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_qos_swe_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diagnose_fabric (struct fabric*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  parse_config (int /*<<< orphan*/ ,struct fabric*,struct torus*) ; 
 int /*<<< orphan*/  report_torus_changes (struct torus*,struct torus*) ; 
 scalar_t__ routable_torus (struct torus*,struct fabric*) ; 
 int route_torus (struct torus*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  teardown_fabric (struct fabric*) ; 
 int /*<<< orphan*/  teardown_torus (struct torus*) ; 
 int /*<<< orphan*/  verify_setup (struct torus*,struct fabric*) ; 

__attribute__((used)) static
int torus_build_lfts(void *context)
{
	int status = -1;
	struct torus_context *ctx = context;
	struct fabric *fabric;
	struct torus *torus;

	if (!ctx->osm->subn.opt.qos) {
		OSM_LOG(&ctx->osm->log, OSM_LOG_ERROR,
			"ERR 4E44: Routing engine list contains torus-2QoS. "
			"Enable QoS for correct operation "
			"(-Q or 'qos TRUE' in opensm.conf).\n");
		return status;
	}

	fabric = &ctx->fabric;
	teardown_fabric(fabric);

	torus = calloc(1, sizeof(*torus));
	if (!torus) {
		OSM_LOG(&ctx->osm->log, OSM_LOG_ERROR,
			"ERR 4E45: allocating torus: %s\n", strerror(errno));
		goto out;
	}
	torus->osm = ctx->osm;
	fabric->osm = ctx->osm;

	if (!parse_config(ctx->osm->subn.opt.torus_conf_file,
			  fabric, torus))
		goto out;

	if (!capture_fabric(fabric))
		goto out;

	OSM_LOG(&torus->osm->log, OSM_LOG_INFO,
		"Found fabric w/ %d links, %d switches, %d CA ports, "
		"minimum data VLs: endport %d, switchport %d\n",
		(int)fabric->link_cnt, (int)fabric->switch_cnt,
		(int)fabric->ca_cnt, (int)ctx->osm->subn.min_data_vls,
		(int)ctx->osm->subn.min_sw_data_vls);

	if (!verify_setup(torus, fabric))
		goto out;

	OSM_LOG(&torus->osm->log, OSM_LOG_INFO,
		"Looking for %d x %d x %d %s\n",
		(int)torus->x_sz, (int)torus->y_sz, (int)torus->z_sz,
		(ALL_MESH(torus->flags) ? "mesh" : "torus"));

	if (!build_torus(fabric, torus)) {
		OSM_LOG(&torus->osm->log, OSM_LOG_ERROR, "ERR 4E57: "
			"build_torus finished with errors\n");
		goto out;
	}

	OSM_LOG(&torus->osm->log, OSM_LOG_INFO,
		"Built %d x %d x %d %s w/ %d links, %d switches, %d CA ports\n",
		(int)torus->x_sz, (int)torus->y_sz, (int)torus->z_sz,
		(ALL_MESH(torus->flags) ? "mesh" : "torus"),
		(int)torus->link_cnt, (int)torus->switch_cnt,
		(int)torus->ca_cnt);

	diagnose_fabric(fabric);
	/*
	 * Since we found some sort of torus fabric, report on any topology
	 * changes vs. the last torus we found.
	 */
	if (torus->flags & NOTIFY_CHANGES)
		report_torus_changes(torus, ctx->torus);

	if (routable_torus(torus, fabric))
		status = route_torus(torus);

out:
	if (status) {		/* bad torus!! */
		if (torus)
			teardown_torus(torus);
	} else {
		osm_subn_opt_t *opt = &torus->osm->subn.opt;
		osm_log_t *log = &torus->osm->log;

		if (ctx->torus)
			teardown_torus(ctx->torus);
		ctx->torus = torus;

		check_qos_swe_config(&opt->qos_swe_options, &opt->qos_options,
				     log);

		check_qos_ep_config(&opt->qos_ca_options,
				    &opt->qos_options, "qos_ca", log);
		check_qos_ep_config(&opt->qos_sw0_options,
				    &opt->qos_options, "qos_sw0", log);
		check_qos_ep_config(&opt->qos_rtr_options,
				    &opt->qos_options, "qos_rtr", log);
	}
	teardown_fabric(fabric);
	return status;
}