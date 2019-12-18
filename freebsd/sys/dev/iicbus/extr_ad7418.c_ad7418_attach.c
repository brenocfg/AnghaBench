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
struct ad7418_softc {int /*<<< orphan*/  sc_lock; scalar_t__ sc_lastupdate; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AD7418_CONF ; 
 int AD7418_CONF_SHUTDOWN ; 
 int CTLFLAG_RD ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct ad7418_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int ad7418_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad7418_sysctl_temp ; 
 int /*<<< orphan*/  ad7418_sysctl_voltage ; 
 int /*<<< orphan*/  ad7418_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ad7418_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 scalar_t__ hz ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ticks ; 

__attribute__((used)) static int
ad7418_attach(device_t dev)
{
	struct ad7418_softc *sc = device_get_softc(dev);
	struct sysctl_ctx_list *ctx = device_get_sysctl_ctx(dev);
	struct sysctl_oid *tree = device_get_sysctl_tree(dev);
	int conf;

	sc->sc_dev = dev;
	sc->sc_lastupdate = ticks - hz;

	sx_init(&sc->sc_lock, "ad7418");

	SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
		"temp", CTLTYPE_INT | CTLFLAG_RD, sc, 0,
		ad7418_sysctl_temp, "I", "operating temperature");
	SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
		"volt", CTLTYPE_INT | CTLFLAG_RD, sc, 0,
		ad7418_sysctl_voltage, "I", "input voltage");

	/* enable chip if configured in shutdown mode */
	conf = ad7418_read_1(dev, AD7418_CONF);
	if (conf >= 0 && (conf & AD7418_CONF_SHUTDOWN))
		ad7418_write_1(dev, AD7418_CONF, conf &~ AD7418_CONF_SHUTDOWN);

	return (0);
}