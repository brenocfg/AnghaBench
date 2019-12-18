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
struct TYPE_2__ {int /*<<< orphan*/ * sync_intr; } ;
struct ath_softc {TYPE_1__ sc_intr_stats; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  sn ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
ath_sysctl_stats_attach_intr(struct ath_softc *sc,
    struct sysctl_oid_list *parent)
{
	struct sysctl_ctx_list *ctx = device_get_sysctl_ctx(sc->sc_dev);
	struct sysctl_oid *tree = device_get_sysctl_tree(sc->sc_dev);
	struct sysctl_oid_list *child = SYSCTL_CHILDREN(tree);
	int i;
	char sn[8];

	tree = SYSCTL_ADD_NODE(ctx, parent, OID_AUTO, "sync_intr",
	    CTLFLAG_RD, NULL, "Sync interrupt statistics");
	child = SYSCTL_CHILDREN(tree);
	for (i = 0; i < 32; i++) {
		snprintf(sn, sizeof(sn), "%d", i);
		SYSCTL_ADD_UINT(ctx, child, OID_AUTO, sn, CTLFLAG_RD,
		    &sc->sc_intr_stats.sync_intr[i], 0, "");
	}
}