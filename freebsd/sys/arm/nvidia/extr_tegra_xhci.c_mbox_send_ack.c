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
typedef  int uint32_t ;
struct tegra_xhci_softc {int dummy; } ;

/* Variables and functions */
 int ARU_MAILBOX_CMD_DEST_FALC ; 
 int ARU_MAILBOX_CMD_INT_EN ; 
 int ARU_MAILBOX_DATA_IN_DATA (int) ; 
 int ARU_MAILBOX_DATA_IN_TYPE (int) ; 
 int FPCI_RD4 (struct tegra_xhci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FPCI_WR4 (struct tegra_xhci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  T_XUSB_CFG_ARU_MAILBOX_CMD ; 
 int /*<<< orphan*/  T_XUSB_CFG_ARU_MAILBOX_DATA_IN ; 

__attribute__((used)) static void
mbox_send_ack(struct tegra_xhci_softc *sc, uint32_t cmd, uint32_t data)
{
	uint32_t reg;

	reg = ARU_MAILBOX_DATA_IN_TYPE(cmd) | ARU_MAILBOX_DATA_IN_DATA(data);
	FPCI_WR4(sc, T_XUSB_CFG_ARU_MAILBOX_DATA_IN, reg);

	reg = FPCI_RD4(sc, T_XUSB_CFG_ARU_MAILBOX_CMD);
	reg |= ARU_MAILBOX_CMD_DEST_FALC | ARU_MAILBOX_CMD_INT_EN;
	FPCI_WR4(sc, T_XUSB_CFG_ARU_MAILBOX_CMD, reg);
}