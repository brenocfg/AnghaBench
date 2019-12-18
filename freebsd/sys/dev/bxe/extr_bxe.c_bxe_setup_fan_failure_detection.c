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
struct TYPE_5__ {int /*<<< orphan*/  shmem2_base; int /*<<< orphan*/  shmem_base; } ;
struct bxe_softc {TYPE_2__ devinfo; } ;
struct TYPE_4__ {int /*<<< orphan*/  config2; } ;
struct TYPE_6__ {TYPE_1__ shared_hw_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int /*<<< orphan*/  MISC_REG_SPIO_EVENT_EN ; 
 int /*<<< orphan*/  MISC_REG_SPIO_INT ; 
 int /*<<< orphan*/  MISC_SPIO_INPUT_HI_Z ; 
 int MISC_SPIO_INT_OLD_SET_POS ; 
 int MISC_SPIO_SPIO5 ; 
 int PORT_0 ; 
 int PORT_MAX ; 
 int REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int) ; 
 int SHARED_HW_CFG_FAN_FAILURE_ENABLED ; 
 int SHARED_HW_CFG_FAN_FAILURE_MASK ; 
 int SHARED_HW_CFG_FAN_FAILURE_PHY_TYPE ; 
 int SHMEM_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_set_spio (struct bxe_softc*,int,int /*<<< orphan*/ ) ; 
 TYPE_3__ dev_info ; 
 int elink_fan_failure_det_req (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bxe_setup_fan_failure_detection(struct bxe_softc *sc)
{
    int is_required;
    uint32_t val;
    int port;

    is_required = 0;
    val = (SHMEM_RD(sc, dev_info.shared_hw_config.config2) &
           SHARED_HW_CFG_FAN_FAILURE_MASK);

    if (val == SHARED_HW_CFG_FAN_FAILURE_ENABLED) {
        is_required = 1;
    }
    /*
     * The fan failure mechanism is usually related to the PHY type since
     * the power consumption of the board is affected by the PHY. Currently,
     * fan is required for most designs with SFX7101, BCM8727 and BCM8481.
     */
    else if (val == SHARED_HW_CFG_FAN_FAILURE_PHY_TYPE) {
        for (port = PORT_0; port < PORT_MAX; port++) {
            is_required |= elink_fan_failure_det_req(sc,
                                                     sc->devinfo.shmem_base,
                                                     sc->devinfo.shmem2_base,
                                                     port);
        }
    }

    BLOGD(sc, DBG_LOAD, "fan detection setting: %d\n", is_required);

    if (is_required == 0) {
        return;
    }

    /* Fan failure is indicated by SPIO 5 */
    bxe_set_spio(sc, MISC_SPIO_SPIO5, MISC_SPIO_INPUT_HI_Z);

    /* set to active low mode */
    val = REG_RD(sc, MISC_REG_SPIO_INT);
    val |= (MISC_SPIO_SPIO5 << MISC_SPIO_INT_OLD_SET_POS);
    REG_WR(sc, MISC_REG_SPIO_INT, val);

    /* enable interrupt to signal the IGU */
    val = REG_RD(sc, MISC_REG_SPIO_EVENT_EN);
    val |= MISC_SPIO_SPIO5;
    REG_WR(sc, MISC_REG_SPIO_EVENT_EN, val);
}