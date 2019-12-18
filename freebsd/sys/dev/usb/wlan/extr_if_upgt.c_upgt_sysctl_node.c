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
struct upgt_stat {int /*<<< orphan*/  st_tx_pending; int /*<<< orphan*/  st_tx_inactive; int /*<<< orphan*/  st_tx_active; } ;
struct upgt_softc {int /*<<< orphan*/  sc_dev; struct upgt_stat sc_stat; } ;
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  UPGT_SYSCTL_STAT_ADD32 (struct sysctl_ctx_list*,struct sysctl_oid_list*,char*,int /*<<< orphan*/ *,char*) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
upgt_sysctl_node(struct upgt_softc *sc)
{
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid_list *child;
	struct sysctl_oid *tree;
	struct upgt_stat *stats;

	stats = &sc->sc_stat;
	ctx = device_get_sysctl_ctx(sc->sc_dev);
	child = SYSCTL_CHILDREN(device_get_sysctl_tree(sc->sc_dev));

	tree = SYSCTL_ADD_NODE(ctx, child, OID_AUTO, "stats", CTLFLAG_RD,
	    NULL, "UPGT statistics");
	child = SYSCTL_CHILDREN(tree);
	UPGT_SYSCTL_STAT_ADD32(ctx, child, "tx_active",
	    &stats->st_tx_active, "Active numbers in TX queue");
	UPGT_SYSCTL_STAT_ADD32(ctx, child, "tx_inactive",
	    &stats->st_tx_inactive, "Inactive numbers in TX queue");
	UPGT_SYSCTL_STAT_ADD32(ctx, child, "tx_pending",
	    &stats->st_tx_pending, "Pending numbers in TX queue");
}