#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iflib_cloneattach_ctx {char const* cc_name; int /*<<< orphan*/  cc_params; scalar_t__ cc_len; struct if_clone* cc_ifc; } ;
struct if_clone {int dummy; } ;
typedef  TYPE_1__* if_pseudo_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_3__ {int /*<<< orphan*/  ip_sctx; int /*<<< orphan*/  ip_dc; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  PSEUDO_LOCK () ; 
 int /*<<< orphan*/  PSEUDO_UNLOCK () ; 
 scalar_t__ __predict_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_print_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int) ; 
 void* device_add_child (int /*<<< orphan*/ *,char const*,int) ; 
 int device_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_quiet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_driver (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_softc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* ifc_name (struct if_clone*) ; 
 TYPE_1__* iflib_ip_lookup (char const*) ; 
 int iflib_pseudo_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct iflib_cloneattach_ctx*) ; 
 int /*<<< orphan*/ * iflib_pseudodev ; 
 int /*<<< orphan*/  iflib_pseudodriver ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/ * root_bus ; 

__attribute__((used)) static int
iflib_clone_create(struct if_clone *ifc, int unit, caddr_t params)
{
	const char *name = ifc_name(ifc);
	struct iflib_cloneattach_ctx clctx;
	if_ctx_t ctx;
	if_pseudo_t ip;
	device_t dev;
	int rc;

	clctx.cc_ifc = ifc;
	clctx.cc_len = 0;
	clctx.cc_params = params;
	clctx.cc_name = name;

	if (__predict_false(iflib_pseudodev == NULL)) {
		/* SYSINIT initialization would panic !?! */
		mtx_lock(&Giant);
		iflib_pseudodev = device_add_child(root_bus, "ifpseudo", 0);
		mtx_unlock(&Giant);
		MPASS(iflib_pseudodev != NULL);
	}
	ip = iflib_ip_lookup(name);
	if (ip == NULL) {
		printf("no ip found for %s\n", name);
		return (ENOENT);
	}
	if ((dev = devclass_get_device(ip->ip_dc, unit)) != NULL) {
		printf("unit %d allocated\n", unit);
		bus_generic_print_child(iflib_pseudodev, dev);
		return (EBUSY);
	}
	PSEUDO_LOCK();
	dev = device_add_child(iflib_pseudodev, name, unit);
	device_set_driver(dev, &iflib_pseudodriver);
	PSEUDO_UNLOCK();
	device_quiet(dev);
	rc = device_attach(dev);
	MPASS(rc == 0);
	MPASS(dev != NULL);
	MPASS(devclass_get_device(ip->ip_dc, unit) == dev);
	rc = iflib_pseudo_register(dev, ip->ip_sctx, &ctx, &clctx);
	if (rc) {
		mtx_lock(&Giant);
		device_delete_child(iflib_pseudodev, dev);
		mtx_unlock(&Giant);
	} else
		device_set_softc(dev, ctx);

	return (rc);
}