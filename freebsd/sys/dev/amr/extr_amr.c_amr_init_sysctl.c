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
struct amr_softc {int /*<<< orphan*/  amr_maxio; int /*<<< orphan*/  amr_dev; int /*<<< orphan*/  amr_busyslots; int /*<<< orphan*/  amr_nextslot; int /*<<< orphan*/  amr_allow_vol_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  CTLFLAG_RW ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
amr_init_sysctl(struct amr_softc *sc)
{

    SYSCTL_ADD_INT(device_get_sysctl_ctx(sc->amr_dev),
	SYSCTL_CHILDREN(device_get_sysctl_tree(sc->amr_dev)),
	OID_AUTO, "allow_volume_configure", CTLFLAG_RW, &sc->amr_allow_vol_config, 0,
	"");
    SYSCTL_ADD_INT(device_get_sysctl_ctx(sc->amr_dev),
	SYSCTL_CHILDREN(device_get_sysctl_tree(sc->amr_dev)),
	OID_AUTO, "nextslot", CTLFLAG_RD, &sc->amr_nextslot, 0,
	"");
    SYSCTL_ADD_INT(device_get_sysctl_ctx(sc->amr_dev),
	SYSCTL_CHILDREN(device_get_sysctl_tree(sc->amr_dev)),
	OID_AUTO, "busyslots", CTLFLAG_RD, &sc->amr_busyslots, 0,
	"");
    SYSCTL_ADD_INT(device_get_sysctl_ctx(sc->amr_dev),
	SYSCTL_CHILDREN(device_get_sysctl_tree(sc->amr_dev)),
	OID_AUTO, "maxio", CTLFLAG_RD, &sc->amr_maxio, 0,
	"");
}