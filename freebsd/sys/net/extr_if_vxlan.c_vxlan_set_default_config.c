#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* sin_port; } ;
struct TYPE_8__ {TYPE_3__ in4; } ;
struct TYPE_5__ {void* sin_port; } ;
struct TYPE_6__ {TYPE_1__ in4; } ;
struct vxlan_softc {int /*<<< orphan*/  vxl_ftable_timeout; int /*<<< orphan*/  vxl_ftable_max; int /*<<< orphan*/  vxl_max_port; int /*<<< orphan*/  vxl_min_port; TYPE_4__ vxl_dst_addr; TYPE_2__ vxl_src_addr; int /*<<< orphan*/  vxl_ttl; int /*<<< orphan*/  vxl_vni; int /*<<< orphan*/  vxl_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPDEFTTL ; 
 int /*<<< orphan*/  VXLAN_FLAG_LEARN ; 
 int /*<<< orphan*/  VXLAN_FTABLE_MAX ; 
 int /*<<< orphan*/  VXLAN_FTABLE_TIMEOUT ; 
 int /*<<< orphan*/  VXLAN_LEGACY_PORT ; 
 int /*<<< orphan*/  VXLAN_PORT ; 
 int /*<<< orphan*/  VXLAN_VNI_MAX ; 
 int /*<<< orphan*/  V_ipport_firstauto ; 
 int /*<<< orphan*/  V_ipport_lastauto ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxlan_legacy_port ; 
 int /*<<< orphan*/  vxlan_tunable_int (struct vxlan_softc*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vxlan_set_default_config(struct vxlan_softc *sc)
{

	sc->vxl_flags |= VXLAN_FLAG_LEARN;

	sc->vxl_vni = VXLAN_VNI_MAX;
	sc->vxl_ttl = IPDEFTTL;

	if (!vxlan_tunable_int(sc, "legacy_port", vxlan_legacy_port)) {
		sc->vxl_src_addr.in4.sin_port = htons(VXLAN_PORT);
		sc->vxl_dst_addr.in4.sin_port = htons(VXLAN_PORT);
	} else {
		sc->vxl_src_addr.in4.sin_port = htons(VXLAN_LEGACY_PORT);
		sc->vxl_dst_addr.in4.sin_port = htons(VXLAN_LEGACY_PORT);
	}

	sc->vxl_min_port = V_ipport_firstauto;
	sc->vxl_max_port = V_ipport_lastauto;

	sc->vxl_ftable_max = VXLAN_FTABLE_MAX;
	sc->vxl_ftable_timeout = VXLAN_FTABLE_TIMEOUT;
}