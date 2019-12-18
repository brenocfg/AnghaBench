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
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct ads111x_softc {int /*<<< orphan*/  lock; int /*<<< orphan*/  cfgword; int /*<<< orphan*/ * chipinfo; int /*<<< orphan*/  dev; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADS111x_CONF ; 
 int /*<<< orphan*/  ADS111x_CONF_DEFAULT ; 
 int CTLFLAG_RWTUN ; 
 int CTLTYPE_INT ; 
 int ENXIO ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct ads111x_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  ads111x_add_channels (struct ads111x_softc*) ; 
 int /*<<< orphan*/ * ads111x_find_chipinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ads111x_sysctl_config ; 
 int /*<<< orphan*/  ads111x_sysctl_hithresh ; 
 int /*<<< orphan*/  ads111x_sysctl_lothresh ; 
 int ads111x_write_2 (struct ads111x_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ads111x_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iicbus_get_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
ads111x_attach(device_t dev)
{
	struct ads111x_softc *sc;
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid *tree;
	int err;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->addr = iicbus_get_addr(dev);
	sc->cfgword = ADS111x_CONF_DEFAULT;

	sc->chipinfo = ads111x_find_chipinfo(sc->dev);
	if (sc->chipinfo == NULL) {
		device_printf(dev,
		    "cannot get chipinfo (but it worked during probe)");
		return (ENXIO);
	}

	/* Set the default chip config. */
	if ((err = ads111x_write_2(sc, ADS111x_CONF, sc->cfgword)) != 0) {
		device_printf(dev, "cannot write chip config register\n");
		return (err);
	}

	/* Add the sysctl handler to set the chip configuration register.  */
	ctx = device_get_sysctl_ctx(dev);
	tree = device_get_sysctl_tree(dev);
	SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
	    "config", CTLTYPE_INT | CTLFLAG_RWTUN, sc, 0,
	    ads111x_sysctl_config, "I", "configuration register word");
	SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
	    "lo_thresh", CTLTYPE_INT | CTLFLAG_RWTUN, sc, 0,
	    ads111x_sysctl_lothresh, "I", "comparator low threshold");
	SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
	    "hi_thresh", CTLTYPE_INT | CTLFLAG_RWTUN, sc, 0,
	    ads111x_sysctl_hithresh, "I", "comparator high threshold");

	/* Set up channels based on metadata or default config. */
	ads111x_add_channels(sc);

	sx_init(&sc->lock, "ads111x");

	return (0);
}