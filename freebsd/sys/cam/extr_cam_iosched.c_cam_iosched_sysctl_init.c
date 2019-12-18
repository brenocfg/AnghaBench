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
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct cam_iosched_softc {int /*<<< orphan*/  max_lat; int /*<<< orphan*/  load; int /*<<< orphan*/  total_ticks; int /*<<< orphan*/  quanta; int /*<<< orphan*/  read_bias; int /*<<< orphan*/  trim_stats; int /*<<< orphan*/  write_stats; int /*<<< orphan*/  read_stats; struct sysctl_ctx_list sysctl_ctx; struct sysctl_oid* sysctl_tree; int /*<<< orphan*/  trim_goal; int /*<<< orphan*/  sort_io_queue; } ;

/* Variables and functions */
 int CTLFLAG_MPSAFE ; 
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_UINT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int,char*) ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_U64 (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  cam_iosched_cl_sysctl_init (struct cam_iosched_softc*) ; 
 int /*<<< orphan*/  cam_iosched_iop_stats_sysctl_init (struct cam_iosched_softc*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cam_iosched_quanta_sysctl ; 
 int /*<<< orphan*/  do_dynamic_iosched ; 

void cam_iosched_sysctl_init(struct cam_iosched_softc *isc,
    struct sysctl_ctx_list *ctx, struct sysctl_oid *node)
{
	struct sysctl_oid_list *n;

	n = SYSCTL_CHILDREN(node);
	SYSCTL_ADD_INT(ctx, n,
		OID_AUTO, "sort_io_queue", CTLFLAG_RW | CTLFLAG_MPSAFE,
		&isc->sort_io_queue, 0,
		"Sort IO queue to try and optimise disk access patterns");
	SYSCTL_ADD_INT(ctx, n,
	    OID_AUTO, "trim_goal", CTLFLAG_RW,
	    &isc->trim_goal, 0,
	    "Number of trims to try to accumulate before sending to hardware");
	SYSCTL_ADD_INT(ctx, n,
	    OID_AUTO, "trim_ticks", CTLFLAG_RW,
	    &isc->trim_goal, 0,
	    "IO Schedul qaunta to hold back trims for when accumulating");

#ifdef CAM_IOSCHED_DYNAMIC
	if (!do_dynamic_iosched)
		return;

	isc->sysctl_tree = SYSCTL_ADD_NODE(&isc->sysctl_ctx,
	    SYSCTL_CHILDREN(node), OID_AUTO, "iosched",
	    CTLFLAG_RD, 0, "I/O scheduler statistics");
	n = SYSCTL_CHILDREN(isc->sysctl_tree);
	ctx = &isc->sysctl_ctx;

	cam_iosched_iop_stats_sysctl_init(isc, &isc->read_stats, "read");
	cam_iosched_iop_stats_sysctl_init(isc, &isc->write_stats, "write");
	cam_iosched_iop_stats_sysctl_init(isc, &isc->trim_stats, "trim");
	cam_iosched_cl_sysctl_init(isc);

	SYSCTL_ADD_INT(ctx, n,
	    OID_AUTO, "read_bias", CTLFLAG_RW,
	    &isc->read_bias, 100,
	    "How biased towards read should we be independent of limits");

	SYSCTL_ADD_PROC(ctx, n,
	    OID_AUTO, "quanta", CTLTYPE_UINT | CTLFLAG_RW,
	    &isc->quanta, 0, cam_iosched_quanta_sysctl, "I",
	    "How many quanta per second do we slice the I/O up into");

	SYSCTL_ADD_INT(ctx, n,
	    OID_AUTO, "total_ticks", CTLFLAG_RD,
	    &isc->total_ticks, 0,
	    "Total number of ticks we've done");

	SYSCTL_ADD_INT(ctx, n,
	    OID_AUTO, "load", CTLFLAG_RD,
	    &isc->load, 0,
	    "scaled load average / 100");

	SYSCTL_ADD_U64(ctx, n,
	    OID_AUTO, "latency_trigger", CTLFLAG_RW,
	    &isc->max_lat, 0,
	    "Latency treshold to trigger callbacks");
#endif
}