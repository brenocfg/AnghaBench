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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct bxe_mf_info {int multi_vnics_mode; int* mf_config; int vnics_per_port; int /*<<< orphan*/  mf_protos_supported; scalar_t__ ext_id; } ;
struct TYPE_3__ {struct bxe_mf_info mf_info; } ;
struct bxe_softc {TYPE_1__ devinfo; } ;
struct TYPE_4__ {int /*<<< orphan*/  e1hov_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,scalar_t__) ; 
 scalar_t__ CHIP_4_PORT_MODE ; 
 scalar_t__ CHIP_PORT_MODE (struct bxe_softc*) ; 
 int FUNC_MF_CFG_PROTOCOL_FCOE ; 
 int FUNC_MF_CFG_PROTOCOL_ISCSI ; 
 int FUNC_MF_CFG_PROTOCOL_MASK ; 
 scalar_t__ MFCFG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MF_PROTO_SUPPORT_ETHERNET ; 
 int /*<<< orphan*/  MF_PROTO_SUPPORT_FCOE ; 
 int /*<<< orphan*/  MF_PROTO_SUPPORT_ISCSI ; 
 size_t SC_ABS_FUNC (struct bxe_softc*) ; 
 size_t SC_VN (struct bxe_softc*) ; 
 int /*<<< orphan*/  VALID_OVLAN (scalar_t__) ; 
 TYPE_2__* func_mf_config ; 

__attribute__((used)) static int
bxe_get_shmem_mf_cfg_info_sd(struct bxe_softc *sc)
{
    struct bxe_mf_info *mf_info = &sc->devinfo.mf_info;
    uint32_t val;

    /* get the outer vlan if we're in switch-dependent mode */

    val = MFCFG_RD(sc, func_mf_config[SC_ABS_FUNC(sc)].e1hov_tag);
    mf_info->ext_id = (uint16_t)val;

    mf_info->multi_vnics_mode = 1;

    if (!VALID_OVLAN(mf_info->ext_id)) {
        BLOGE(sc, "Invalid VLAN (%d)\n", mf_info->ext_id);
        return (1);
    }

    /* get the capabilities */
    if ((mf_info->mf_config[SC_VN(sc)] & FUNC_MF_CFG_PROTOCOL_MASK) ==
        FUNC_MF_CFG_PROTOCOL_ISCSI) {
        mf_info->mf_protos_supported |= MF_PROTO_SUPPORT_ISCSI;
    } else if ((mf_info->mf_config[SC_VN(sc)] & FUNC_MF_CFG_PROTOCOL_MASK) ==
               FUNC_MF_CFG_PROTOCOL_FCOE) {
        mf_info->mf_protos_supported |= MF_PROTO_SUPPORT_FCOE;
    } else {
        mf_info->mf_protos_supported |= MF_PROTO_SUPPORT_ETHERNET;
    }

    mf_info->vnics_per_port =
        (CHIP_PORT_MODE(sc) == CHIP_4_PORT_MODE) ? 2 : 4;

    return (0);
}