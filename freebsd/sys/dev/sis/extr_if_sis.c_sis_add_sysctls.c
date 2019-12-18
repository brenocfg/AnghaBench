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
struct sysctl_ctx_list {int dummy; } ;
struct sis_softc {scalar_t__ sis_manual_pad; int /*<<< orphan*/  sis_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RWTUN ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sis_add_sysctls(struct sis_softc *sc)
{
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid_list *children;
	int unit;

	ctx = device_get_sysctl_ctx(sc->sis_dev);
	children = SYSCTL_CHILDREN(device_get_sysctl_tree(sc->sis_dev));

	unit = device_get_unit(sc->sis_dev);
	/*
	 * Unlike most other controllers, NS DP83815/DP83816 controllers
	 * seem to pad with 0xFF when it encounter short frames.  According
	 * to RFC 1042 the pad bytes should be 0x00.  Turning this tunable
	 * on will have driver pad manully but it's disabled by default
	 * because it will consume extra CPU cycles for short frames.
	 */
	sc->sis_manual_pad = 0;
	SYSCTL_ADD_INT(ctx, children, OID_AUTO, "manual_pad",
	    CTLFLAG_RWTUN, &sc->sis_manual_pad, 0, "Manually pad short frames");
}