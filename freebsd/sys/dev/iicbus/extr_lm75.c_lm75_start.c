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
struct lm75_softc {scalar_t__ sc_hwtype; int /*<<< orphan*/  enum_hook; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int CTLFLAG_MPSAFE ; 
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int CTLTYPE_STRING ; 
 int CTLTYPE_UINT ; 
 scalar_t__ HWTYPE_LM75A ; 
 int /*<<< orphan*/  LM75_TEMP ; 
 int /*<<< orphan*/  LM75_THYST ; 
 int /*<<< orphan*/  LM75_TOS ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 struct lm75_softc* device_get_softc (scalar_t__) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (scalar_t__) ; 
 struct sysctl_oid* device_get_sysctl_tree (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (scalar_t__,char*) ; 
 int /*<<< orphan*/  lm75_faults_sysctl ; 
 int /*<<< orphan*/  lm75_mode_sysctl ; 
 int /*<<< orphan*/  lm75_pol_sysctl ; 
 int /*<<< orphan*/  lm75_shutdown_sysctl ; 
 int /*<<< orphan*/  lm75_temp_sysctl ; 
 scalar_t__ lm75_type_detect (struct lm75_softc*) ; 

__attribute__((used)) static void
lm75_start(void *xdev)
{
	device_t dev;
	struct lm75_softc *sc;
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid *tree_node;
	struct sysctl_oid_list *tree;

	dev = (device_t)xdev;
	sc = device_get_softc(dev);
	ctx = device_get_sysctl_ctx(dev);
	tree_node = device_get_sysctl_tree(dev);
	tree = SYSCTL_CHILDREN(tree_node);

	config_intrhook_disestablish(&sc->enum_hook);

	/*
	 * Detect the kind of chip we are attaching to.
	 * This may not work for LM75 clones.
	 */
	if (lm75_type_detect(sc) != 0) {
		device_printf(dev, "cannot read from sensor.\n");
		return;
	}
	if (sc->sc_hwtype == HWTYPE_LM75A)
		device_printf(dev,
		    "LM75A type sensor detected (11bits resolution).\n");

	/* Temperature. */
	SYSCTL_ADD_PROC(ctx, tree, OID_AUTO, "temperature",
	    CTLTYPE_INT | CTLFLAG_RD | CTLFLAG_MPSAFE, dev, LM75_TEMP,
	    lm75_temp_sysctl, "IK", "Current temperature");
	SYSCTL_ADD_PROC(ctx, tree, OID_AUTO, "thyst",
	    CTLTYPE_INT | CTLFLAG_RW | CTLFLAG_MPSAFE, dev, LM75_THYST,
	    lm75_temp_sysctl, "IK", "Hysteresis temperature");
	SYSCTL_ADD_PROC(ctx, tree, OID_AUTO, "tos",
	    CTLTYPE_INT | CTLFLAG_RW | CTLFLAG_MPSAFE, dev, LM75_TOS,
	    lm75_temp_sysctl, "IK", "Overtemperature");

	/* Configuration parameters. */
	SYSCTL_ADD_PROC(ctx, tree, OID_AUTO, "faults",
	    CTLFLAG_RW | CTLTYPE_UINT | CTLFLAG_MPSAFE, dev, 0,
	    lm75_faults_sysctl, "IU", "LM75 fault queue");
	SYSCTL_ADD_PROC(ctx, tree, OID_AUTO, "mode",
	    CTLFLAG_RW | CTLTYPE_STRING | CTLFLAG_MPSAFE, dev, 0,
	    lm75_mode_sysctl, "A", "LM75 mode");
	SYSCTL_ADD_PROC(ctx, tree, OID_AUTO, "polarity",
	    CTLFLAG_RW | CTLTYPE_STRING | CTLFLAG_MPSAFE, dev, 0,
	    lm75_pol_sysctl, "A", "LM75 OS polarity");
	SYSCTL_ADD_PROC(ctx, tree, OID_AUTO, "shutdown",
	    CTLFLAG_RW | CTLTYPE_UINT | CTLFLAG_MPSAFE, dev, 0,
	    lm75_shutdown_sysctl, "IU", "LM75 shutdown");
}