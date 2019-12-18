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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {scalar_t__ duplex; int flow_ctrl; int /*<<< orphan*/  link_up; } ;
struct bxe_softc {int flags; TYPE_1__ link_vars; } ;
struct bxe_link_report_data {int /*<<< orphan*/  link_report_flags; int /*<<< orphan*/  line_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  BXE_LINK_REPORT_FULL_DUPLEX ; 
 int /*<<< orphan*/  BXE_LINK_REPORT_LINK_DOWN ; 
 int /*<<< orphan*/  BXE_LINK_REPORT_RX_FC_ON ; 
 int /*<<< orphan*/  BXE_LINK_REPORT_TX_FC_ON ; 
 int BXE_MF_FUNC_DIS ; 
 scalar_t__ DUPLEX_FULL ; 
 int ELINK_FLOW_CTRL_RX ; 
 int ELINK_FLOW_CTRL_TX ; 
 int /*<<< orphan*/  bxe_get_mf_speed (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct bxe_link_report_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bxe_fill_report_data(struct bxe_softc            *sc,
                     struct bxe_link_report_data *data)
{
    uint16_t line_speed = bxe_get_mf_speed(sc);

    memset(data, 0, sizeof(*data));

    /* fill the report data with the effective line speed */
    data->line_speed = line_speed;

    /* Link is down */
    if (!sc->link_vars.link_up || (sc->flags & BXE_MF_FUNC_DIS)) {
        bxe_set_bit(BXE_LINK_REPORT_LINK_DOWN, &data->link_report_flags);
    }

    /* Full DUPLEX */
    if (sc->link_vars.duplex == DUPLEX_FULL) {
        bxe_set_bit(BXE_LINK_REPORT_FULL_DUPLEX, &data->link_report_flags);
    }

    /* Rx Flow Control is ON */
    if (sc->link_vars.flow_ctrl & ELINK_FLOW_CTRL_RX) {
        bxe_set_bit(BXE_LINK_REPORT_RX_FC_ON, &data->link_report_flags);
    }

    /* Tx Flow Control is ON */
    if (sc->link_vars.flow_ctrl & ELINK_FLOW_CTRL_TX) {
        bxe_set_bit(BXE_LINK_REPORT_TX_FC_ON, &data->link_report_flags);
    }
}