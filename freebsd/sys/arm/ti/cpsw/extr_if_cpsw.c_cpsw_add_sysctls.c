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
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct cpsw_softc {int active_slave; int /*<<< orphan*/  rx; int /*<<< orphan*/  tx; int /*<<< orphan*/  dualemac; int /*<<< orphan*/  debug; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {char* oid; } ;

/* Variables and functions */
 int CPSW_PORTS ; 
 int CPSW_SYSCTL_COUNT ; 
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_U64 ; 
 int CTLTYPE_UINT ; 
 int OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int,char*,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int,char*,int,struct cpsw_softc*,int,int /*<<< orphan*/ ,char*,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  cpsw_add_queue_sysctls (struct sysctl_ctx_list*,struct sysctl_oid*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpsw_add_watchdog_sysctls (struct sysctl_ctx_list*,struct sysctl_oid*,struct cpsw_softc*) ; 
 int /*<<< orphan*/  cpsw_intr_coalesce ; 
 int /*<<< orphan*/  cpsw_stat_attached ; 
 TYPE_1__* cpsw_stat_sysctls ; 
 int /*<<< orphan*/  cpsw_stat_uptime ; 
 int /*<<< orphan*/  cpsw_stats_sysctl ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cpsw_add_sysctls(struct cpsw_softc *sc)
{
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid *stats_node, *queue_node, *node;
	struct sysctl_oid_list *parent, *stats_parent, *queue_parent;
	struct sysctl_oid_list *ports_parent, *port_parent;
	char port[16];
	int i;

	ctx = device_get_sysctl_ctx(sc->dev);
	parent = SYSCTL_CHILDREN(device_get_sysctl_tree(sc->dev));

	SYSCTL_ADD_INT(ctx, parent, OID_AUTO, "debug",
	    CTLFLAG_RW, &sc->debug, 0, "Enable switch debug messages");

	SYSCTL_ADD_PROC(ctx, parent, OID_AUTO, "attachedSecs",
	    CTLTYPE_UINT | CTLFLAG_RD, sc, 0, cpsw_stat_attached, "IU",
	    "Time since driver attach");

	SYSCTL_ADD_PROC(ctx, parent, OID_AUTO, "intr_coalesce_us",
	    CTLTYPE_UINT | CTLFLAG_RW, sc, 0, cpsw_intr_coalesce, "IU",
	    "minimum time between interrupts");

	node = SYSCTL_ADD_NODE(ctx, parent, OID_AUTO, "ports",
	    CTLFLAG_RD, NULL, "CPSW Ports Statistics");
	ports_parent = SYSCTL_CHILDREN(node);
	for (i = 0; i < CPSW_PORTS; i++) {
		if (!sc->dualemac && i != sc->active_slave)
			continue;
		port[0] = '0' + i;
		port[1] = '\0';
		node = SYSCTL_ADD_NODE(ctx, ports_parent, OID_AUTO,
		    port, CTLFLAG_RD, NULL, "CPSW Port Statistics");
		port_parent = SYSCTL_CHILDREN(node);
		SYSCTL_ADD_PROC(ctx, port_parent, OID_AUTO, "uptime",
		    CTLTYPE_UINT | CTLFLAG_RD, sc, i,
		    cpsw_stat_uptime, "IU", "Seconds since driver init");
	}

	stats_node = SYSCTL_ADD_NODE(ctx, parent, OID_AUTO, "stats",
				     CTLFLAG_RD, NULL, "CPSW Statistics");
	stats_parent = SYSCTL_CHILDREN(stats_node);
	for (i = 0; i < CPSW_SYSCTL_COUNT; ++i) {
		SYSCTL_ADD_PROC(ctx, stats_parent, i,
				cpsw_stat_sysctls[i].oid,
				CTLTYPE_U64 | CTLFLAG_RD, sc, 0,
				cpsw_stats_sysctl, "IU",
				cpsw_stat_sysctls[i].oid);
	}

	queue_node = SYSCTL_ADD_NODE(ctx, parent, OID_AUTO, "queue",
	    CTLFLAG_RD, NULL, "CPSW Queue Statistics");
	queue_parent = SYSCTL_CHILDREN(queue_node);

	node = SYSCTL_ADD_NODE(ctx, queue_parent, OID_AUTO, "tx",
	    CTLFLAG_RD, NULL, "TX Queue Statistics");
	cpsw_add_queue_sysctls(ctx, node, &sc->tx);

	node = SYSCTL_ADD_NODE(ctx, queue_parent, OID_AUTO, "rx",
	    CTLFLAG_RD, NULL, "RX Queue Statistics");
	cpsw_add_queue_sysctls(ctx, node, &sc->rx);

	node = SYSCTL_ADD_NODE(ctx, parent, OID_AUTO, "watchdog",
	    CTLFLAG_RD, NULL, "Watchdog Statistics");
	cpsw_add_watchdog_sysctls(ctx, node, sc);
}