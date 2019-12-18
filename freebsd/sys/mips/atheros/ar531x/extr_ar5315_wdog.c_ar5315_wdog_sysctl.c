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
struct ar5315_wdog_softc {int /*<<< orphan*/  reboot_from_watchdog; int /*<<< orphan*/  armed; int /*<<< orphan*/  debug; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  CTLFLAG_RW ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct ar5315_wdog_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ar5315_wdog_sysctl(device_t dev)
{
	struct ar5315_wdog_softc *sc = device_get_softc(dev);

        struct sysctl_ctx_list *ctx = device_get_sysctl_ctx(sc->dev);
        struct sysctl_oid *tree = device_get_sysctl_tree(sc->dev);

        SYSCTL_ADD_INT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
                "debug", CTLFLAG_RW, &sc->debug, 0,
                "enable watchdog debugging");
        SYSCTL_ADD_INT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
                "armed", CTLFLAG_RD, &sc->armed, 0,
                "whether the watchdog is armed");
        SYSCTL_ADD_INT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
                "reboot_from_watchdog", CTLFLAG_RD, &sc->reboot_from_watchdog, 0,
                "whether the system rebooted from the watchdog");
}