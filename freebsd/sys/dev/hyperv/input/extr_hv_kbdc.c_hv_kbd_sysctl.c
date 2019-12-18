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
struct sysctl_oid_list {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  debug; } ;
typedef  TYPE_1__ hv_kbd_sc ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RW ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hv_kbd_sysctl(device_t dev)
{
	struct sysctl_oid_list *child;
	struct sysctl_ctx_list *ctx;
	hv_kbd_sc *sc;

	sc = device_get_softc(dev);
	ctx = device_get_sysctl_ctx(dev);
	child = SYSCTL_CHILDREN(device_get_sysctl_tree(dev));
	SYSCTL_ADD_INT(ctx, child, OID_AUTO, "debug", CTLFLAG_RW,
	    &sc->debug, 0, "debug hyperv keyboard");
}