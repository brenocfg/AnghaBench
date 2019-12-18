#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct bxe_mf_info {int multi_vnics_mode; int vnics_per_port; int /*<<< orphan*/  mf_protos_supported; } ;
struct TYPE_3__ {struct bxe_mf_info mf_info; } ;
struct bxe_softc {TYPE_1__ devinfo; } ;
struct TYPE_4__ {int /*<<< orphan*/  func_cfg; } ;

/* Variables and functions */
 scalar_t__ CHIP_4_PORT_MODE ; 
 scalar_t__ CHIP_PORT_MODE (struct bxe_softc*) ; 
 int MACP_FUNC_CFG_FLAGS_MASK ; 
 int MFCFG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 size_t SC_ABS_FUNC (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_get_shmem_ext_proto_support_flags (struct bxe_softc*) ; 
 TYPE_2__* func_ext_config ; 

__attribute__((used)) static int
bxe_get_shmem_mf_cfg_info_si(struct bxe_softc *sc)
{
    struct bxe_mf_info *mf_info = &sc->devinfo.mf_info;
    uint32_t val;

    /*
     * There is no outer vlan if we're in switch-independent mode.
     * If the mac is valid then assume multi-function.
     */

    val = MFCFG_RD(sc, func_ext_config[SC_ABS_FUNC(sc)].func_cfg);

    mf_info->multi_vnics_mode = ((val & MACP_FUNC_CFG_FLAGS_MASK) != 0);

    mf_info->mf_protos_supported = bxe_get_shmem_ext_proto_support_flags(sc);

    mf_info->vnics_per_port =
        (CHIP_PORT_MODE(sc) == CHIP_4_PORT_MODE) ? 2 : 4;

    return (0);
}