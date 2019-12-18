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
struct sysctl_ctx_list {int dummy; } ;
struct icee_softc {scalar_t__ size; scalar_t__ type; scalar_t__ wr_sz; TYPE_1__* cdev; int /*<<< orphan*/  dev; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {struct icee_softc* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UID_ROOT ; 
 scalar_t__ bootverbose ; 
 struct icee_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  icee_cdevsw ; 
 int /*<<< orphan*/  icee_init (struct icee_softc*) ; 
 int /*<<< orphan*/  iicbus_get_addr (int /*<<< orphan*/ ) ; 
 TYPE_1__* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
icee_attach(device_t dev)
{
	struct icee_softc *sc = device_get_softc(dev);
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid_list *tree;

	sc->dev = dev;
	sc->addr = iicbus_get_addr(dev);
	icee_init(sc);
	if (sc->size == 0 || sc->type == 0 || sc->wr_sz == 0) {
		device_printf(sc->dev, "Missing config data, "
		    "these cannot be zero: size %d type %d wr_sz %d\n",
		    sc->size, sc->type, sc->wr_sz);
		return (EINVAL);
	}
	if (bootverbose)
		device_printf(dev, "size: %d bytes, addressing: %d-bits\n",
		    sc->size, sc->type);
	sc->cdev = make_dev(&icee_cdevsw, device_get_unit(dev), UID_ROOT,
	    GID_WHEEL, 0600, "icee%d", device_get_unit(dev));
	if (sc->cdev == NULL) {
		return (ENOMEM);
	}
	sc->cdev->si_drv1 = sc;

	ctx = device_get_sysctl_ctx(dev);
	tree = SYSCTL_CHILDREN(device_get_sysctl_tree(dev));
	SYSCTL_ADD_INT(ctx, tree, OID_AUTO, "address_size", CTLFLAG_RD,
	    &sc->type, 0, "Memory array address size in bits");
	SYSCTL_ADD_INT(ctx, tree, OID_AUTO, "device_size", CTLFLAG_RD,
	    &sc->size, 0, "Memory array capacity in bytes");
	SYSCTL_ADD_INT(ctx, tree, OID_AUTO, "write_size", CTLFLAG_RD,
	    &sc->wr_sz, 0, "Memory array page write size in bytes");

	return (0);
}