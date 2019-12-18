#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ecore_func_start_params {int /*<<< orphan*/  network_cos_mode; int /*<<< orphan*/  sd_vlan_tag; int /*<<< orphan*/  mf_mode; } ;
struct TYPE_6__ {struct ecore_func_start_params start; } ;
struct ecore_func_state_params {int /*<<< orphan*/  cmd; int /*<<< orphan*/ * f_obj; int /*<<< orphan*/  ramrod_flags; TYPE_3__ params; int /*<<< orphan*/ * member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/  mf_mode; } ;
struct TYPE_5__ {TYPE_1__ mf_info; } ;
struct bxe_softc {TYPE_2__ devinfo; int /*<<< orphan*/  func_obj; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E2 (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E3 (struct bxe_softc*) ; 
 int /*<<< orphan*/  ECORE_F_CMD_START ; 
 int /*<<< orphan*/  FW_WRR ; 
 int /*<<< orphan*/  OVLAN (struct bxe_softc*) ; 
 int /*<<< orphan*/  RAMROD_COMP_WAIT ; 
 int /*<<< orphan*/  STATIC_COS ; 
 int /*<<< orphan*/  bit_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ecore_func_state_change (struct bxe_softc*,struct ecore_func_state_params*) ; 

__attribute__((used)) static inline int
bxe_func_start(struct bxe_softc *sc)
{
    struct ecore_func_state_params func_params = { NULL };
    struct ecore_func_start_params *start_params = &func_params.params.start;

    /* Prepare parameters for function state transitions */
    bit_set(&func_params.ramrod_flags, RAMROD_COMP_WAIT);

    func_params.f_obj = &sc->func_obj;
    func_params.cmd = ECORE_F_CMD_START;

    /* Function parameters */
    start_params->mf_mode     = sc->devinfo.mf_info.mf_mode;
    start_params->sd_vlan_tag = OVLAN(sc);

    if (CHIP_IS_E2(sc) || CHIP_IS_E3(sc)) {
        start_params->network_cos_mode = STATIC_COS;
    } else { /* CHIP_IS_E1X */
        start_params->network_cos_mode = FW_WRR;
    }

    //start_params->gre_tunnel_mode = 0;
    //start_params->gre_tunnel_rss  = 0;

    return (ecore_func_state_change(sc, &func_params));
}