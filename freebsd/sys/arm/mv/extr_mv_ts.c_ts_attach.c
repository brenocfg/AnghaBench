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
struct sysctl_ctx_list {int dummy; } ;
struct mvts_softc {int /*<<< orphan*/  sc_res; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLTYPE_INT ; 
 int ENXIO ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mvts_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mvts_res ; 
 int /*<<< orphan*/  ts_sysctl_handler ; 

__attribute__((used)) static int
ts_attach(device_t dev)
{
	struct mvts_softc *sc;
	struct sysctl_ctx_list *ctx;
	int error;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	error = bus_alloc_resources(dev, mvts_res, sc->sc_res);
	if (error) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}
	ctx = device_get_sysctl_ctx(dev);
	SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
	    OID_AUTO, "temperature", CTLTYPE_INT | CTLFLAG_RD, dev,
	    0, ts_sysctl_handler, "IK", "Current Temperature");

	return (0);
}