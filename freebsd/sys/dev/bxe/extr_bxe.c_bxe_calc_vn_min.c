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
typedef  int uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  cmng_enables; } ;
struct cmng_init_input {int* vnic_min_rate; TYPE_3__ flags; } ;
struct TYPE_4__ {int* mf_config; } ;
struct TYPE_5__ {TYPE_1__ mf_info; } ;
struct bxe_softc {TYPE_2__ devinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ BXE_IS_ETS_ENABLED (struct bxe_softc*) ; 
 int /*<<< orphan*/  CMNG_FLAGS_PER_PORT_FAIRNESS_VN ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int DEF_MIN_RATE ; 
 int FUNC_MF_CFG_FUNC_HIDE ; 
 int FUNC_MF_CFG_MIN_BW_MASK ; 
 int FUNC_MF_CFG_MIN_BW_SHIFT ; 
 int SC_MAX_VN_NUM (struct bxe_softc*) ; 
 int VN_0 ; 

__attribute__((used)) static void
bxe_calc_vn_min(struct bxe_softc       *sc,
                struct cmng_init_input *input)
{
    uint32_t vn_cfg;
    uint32_t vn_min_rate;
    int all_zero = 1;
    int vn;

    for (vn = VN_0; vn < SC_MAX_VN_NUM(sc); vn++) {
        vn_cfg = sc->devinfo.mf_info.mf_config[vn];
        vn_min_rate = (((vn_cfg & FUNC_MF_CFG_MIN_BW_MASK) >>
                        FUNC_MF_CFG_MIN_BW_SHIFT) * 100);

        if (vn_cfg & FUNC_MF_CFG_FUNC_HIDE) {
            /* skip hidden VNs */
            vn_min_rate = 0;
        } else if (!vn_min_rate) {
            /* If min rate is zero - set it to 100 */
            vn_min_rate = DEF_MIN_RATE;
        } else {
            all_zero = 0;
        }

        input->vnic_min_rate[vn] = vn_min_rate;
    }

    /* if ETS or all min rates are zeros - disable fairness */
    if (BXE_IS_ETS_ENABLED(sc)) {
        input->flags.cmng_enables &= ~CMNG_FLAGS_PER_PORT_FAIRNESS_VN;
        BLOGD(sc, DBG_LOAD, "Fairness disabled (ETS)\n");
    } else if (all_zero) {
        input->flags.cmng_enables &= ~CMNG_FLAGS_PER_PORT_FAIRNESS_VN;
        BLOGD(sc, DBG_LOAD,
              "Fariness disabled (all MIN values are zeroes)\n");
    } else {
        input->flags.cmng_enables |= CMNG_FLAGS_PER_PORT_FAIRNESS_VN;
    }
}