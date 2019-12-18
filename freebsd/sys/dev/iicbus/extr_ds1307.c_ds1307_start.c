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
typedef  int uint8_t ;
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct ds1307_softc {int /*<<< orphan*/  sc_dev; scalar_t__ sc_mcp7941x; int /*<<< orphan*/  enum_hook; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCKF_SETTIME_NO_ADJ ; 
 int CTLFLAG_MPSAFE ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_UINT ; 
 int /*<<< orphan*/  DS1307_SECS ; 
 int DS1307_SECS_CH ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,struct ds1307_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  clock_register_flags (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clock_schedule (scalar_t__,int) ; 
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 struct ds1307_softc* device_get_softc (scalar_t__) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (scalar_t__) ; 
 struct sysctl_oid* device_get_sysctl_tree (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ds1307_read1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ds1307_sqw_freq_sysctl ; 
 int /*<<< orphan*/  ds1307_sqw_out_sysctl ; 
 int /*<<< orphan*/  ds1307_sqwe_sysctl ; 

__attribute__((used)) static void
ds1307_start(void *xdev)
{
	device_t dev;
	struct ds1307_softc *sc;
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid *tree_node;
	struct sysctl_oid_list *tree;
	uint8_t secs;
	uint8_t osc_en;

	dev = (device_t)xdev;
	sc = device_get_softc(dev);
	ctx = device_get_sysctl_ctx(dev);
	tree_node = device_get_sysctl_tree(dev);
	tree = SYSCTL_CHILDREN(tree_node);

	config_intrhook_disestablish(&sc->enum_hook);

	/* Check if the oscillator is disabled. */
	if (ds1307_read1(sc->sc_dev, DS1307_SECS, &secs) != 0) {
		device_printf(sc->sc_dev, "cannot read from RTC.\n");
		return;
	}
	if (sc->sc_mcp7941x)
		osc_en = 0x80;
	else
		osc_en = 0x00;

	if (((secs & DS1307_SECS_CH) ^ osc_en) != 0) {
		device_printf(sc->sc_dev,
		    "WARNING: RTC clock stopped, check the battery.\n");
	}

	/* Configuration parameters. */
	SYSCTL_ADD_PROC(ctx, tree, OID_AUTO, "sqwe",
	    CTLFLAG_RW | CTLTYPE_UINT | CTLFLAG_MPSAFE, sc, 0,
	    ds1307_sqwe_sysctl, "IU", "DS1307 square-wave enable");
	SYSCTL_ADD_PROC(ctx, tree, OID_AUTO, "sqw_freq",
	    CTLFLAG_RW | CTLTYPE_UINT | CTLFLAG_MPSAFE, sc, 0,
	    ds1307_sqw_freq_sysctl, "IU",
	    "DS1307 square-wave output frequency");
	SYSCTL_ADD_PROC(ctx, tree, OID_AUTO, "sqw_out",
	    CTLFLAG_RW | CTLTYPE_UINT | CTLFLAG_MPSAFE, sc, 0,
	    ds1307_sqw_out_sysctl, "IU", "DS1307 square-wave output state");

	/*
	 * Register as a clock with 1 second resolution.  Schedule the
	 * clock_settime() method to be called just after top-of-second;
	 * resetting the time resets top-of-second in the hardware.
	 */
	clock_register_flags(dev, 1000000, CLOCKF_SETTIME_NO_ADJ);
	clock_schedule(dev, 1);
}