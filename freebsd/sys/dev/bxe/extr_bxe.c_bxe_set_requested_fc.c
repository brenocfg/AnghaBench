#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  req_fc_auto_adv; } ;
struct bxe_softc {int mtu; TYPE_1__ link_params; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1x (struct bxe_softc*) ; 
 int /*<<< orphan*/  ELINK_FLOW_CTRL_BOTH ; 
 int /*<<< orphan*/  ELINK_FLOW_CTRL_TX ; 

__attribute__((used)) static void
bxe_set_requested_fc(struct bxe_softc *sc)
{
    /*
     * Initialize link parameters structure variables
     * It is recommended to turn off RX FC for jumbo frames
     * for better performance
     */
    if (CHIP_IS_E1x(sc) && (sc->mtu > 5000)) {
        sc->link_params.req_fc_auto_adv = ELINK_FLOW_CTRL_TX;
    } else {
        sc->link_params.req_fc_auto_adv = ELINK_FLOW_CTRL_BOTH;
    }
}