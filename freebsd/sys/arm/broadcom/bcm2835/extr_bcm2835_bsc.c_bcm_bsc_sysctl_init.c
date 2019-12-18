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
struct bcm_bsc_softc {int /*<<< orphan*/  sc_debug; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int CTLFLAG_RW ; 
 int /*<<< orphan*/  CTLFLAG_RWTUN ; 
 int CTLTYPE_UINT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,struct bcm_bsc_softc*,int,int /*<<< orphan*/ ,char*,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  bcm_bsc_clkt_proc ; 
 int /*<<< orphan*/  bcm_bsc_clock_proc ; 
 int /*<<< orphan*/  bcm_bsc_fall_proc ; 
 int /*<<< orphan*/  bcm_bsc_rise_proc ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bcm_bsc_sysctl_init(struct bcm_bsc_softc *sc)
{
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid *tree_node;
	struct sysctl_oid_list *tree;

	/*
	 * Add system sysctl tree/handlers.
	 */
	ctx = device_get_sysctl_ctx(sc->sc_dev);
	tree_node = device_get_sysctl_tree(sc->sc_dev);
	tree = SYSCTL_CHILDREN(tree_node);
	SYSCTL_ADD_PROC(ctx, tree, OID_AUTO, "frequency",
	    CTLFLAG_RW | CTLTYPE_UINT, sc, sizeof(*sc),
	    bcm_bsc_clock_proc, "IU", "I2C BUS clock frequency");
	SYSCTL_ADD_PROC(ctx, tree, OID_AUTO, "clock_stretch",
	    CTLFLAG_RW | CTLTYPE_UINT, sc, sizeof(*sc),
	    bcm_bsc_clkt_proc, "IU", "I2C BUS clock stretch timeout");
	SYSCTL_ADD_PROC(ctx, tree, OID_AUTO, "fall_edge_delay",
	    CTLFLAG_RW | CTLTYPE_UINT, sc, sizeof(*sc),
	    bcm_bsc_fall_proc, "IU", "I2C BUS falling edge delay");
	SYSCTL_ADD_PROC(ctx, tree, OID_AUTO, "rise_edge_delay",
	    CTLFLAG_RW | CTLTYPE_UINT, sc, sizeof(*sc),
	    bcm_bsc_rise_proc, "IU", "I2C BUS rising edge delay");
	SYSCTL_ADD_INT(ctx, tree, OID_AUTO, "debug",
	    CTLFLAG_RWTUN, &sc->sc_debug, 0,
	    "Enable debug; 1=reads/writes, 2=add starts/stops");
}