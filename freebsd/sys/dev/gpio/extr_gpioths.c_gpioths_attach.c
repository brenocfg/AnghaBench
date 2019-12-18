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
struct gpioths_softc {void* fails_oid; void* hum_oid; void* temp_oid; int /*<<< orphan*/  callout; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLTYPE_INT ; 
 int GPIOTHS_POLLTIME ; 
 int /*<<< orphan*/  OID_AUTO ; 
 void* SYSCTL_ADD_PROC (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct gpioths_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gpioths_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpioths_fails_sysctl ; 
 int /*<<< orphan*/  gpioths_hum_sysctl ; 
 int /*<<< orphan*/  gpioths_poll ; 
 int /*<<< orphan*/  gpioths_temp_sysctl ; 
 int hz ; 

__attribute__((used)) static int
gpioths_attach(device_t dev)
{
	struct gpioths_softc	*sc;
	struct sysctl_ctx_list	*ctx;
	struct sysctl_oid	*tree;

	sc = device_get_softc(dev);
	ctx = device_get_sysctl_ctx(dev);
	tree = device_get_sysctl_tree(dev);

	sc->dev = dev;

	callout_init(&sc->callout, 1);
	callout_reset(&sc->callout, GPIOTHS_POLLTIME * hz, gpioths_poll, dev);

	sc->temp_oid = SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
	    "temperature", CTLTYPE_INT | CTLFLAG_RD, sc, 0,
	    gpioths_temp_sysctl, "I", "temperature(C)");

	sc->hum_oid = SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
	    "humidity", CTLTYPE_INT | CTLFLAG_RD, sc, 0,
	    gpioths_hum_sysctl, "I", "humidity(%)");

	sc->fails_oid = SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
	    "fails", CTLTYPE_INT | CTLFLAG_RD, sc, 0,
	    gpioths_fails_sysctl, "I", "fails since last successful read");

	return (0);
}