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
struct intr_info {char* name; int fatal; int /*<<< orphan*/ * actions; struct intr_details const* details; scalar_t__ flags; void* enable_reg; void* cause_reg; } ;
struct intr_details {int member_0; char* member_1; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  A_MAC_PORT_INT_CAUSE ; 
 int /*<<< orphan*/  A_MAC_PORT_INT_EN ; 
 int /*<<< orphan*/  A_MAC_PORT_PERR_INT_CAUSE ; 
 int /*<<< orphan*/  A_MAC_PORT_PERR_INT_CAUSE_100G ; 
 int /*<<< orphan*/  A_MAC_PORT_PERR_INT_EN ; 
 int /*<<< orphan*/  A_MAC_PORT_PERR_INT_EN_100G ; 
 int /*<<< orphan*/  A_XGMAC_PORT_INT_CAUSE ; 
 int /*<<< orphan*/  A_XGMAC_PORT_INT_EN ; 
 scalar_t__ CHELSIO_T5 ; 
 scalar_t__ CHELSIO_T6 ; 
#define  F_RXFIFO_PRTY_ERR 129 
#define  F_TXFIFO_PRTY_ERR 128 
 void* PORT_REG (int,int /*<<< orphan*/ ) ; 
 void* T5_PORT_REG (int,int /*<<< orphan*/ ) ; 
 scalar_t__ chip_id (struct adapter*) ; 
 scalar_t__ is_t4 (struct adapter*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int t4_handle_intr (struct adapter*,struct intr_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool mac_intr_handler(struct adapter *adap, int port, bool verbose)
{
	static const struct intr_details mac_intr_details[] = {
		{ F_TXFIFO_PRTY_ERR, "MAC Tx FIFO parity error" },
		{ F_RXFIFO_PRTY_ERR, "MAC Rx FIFO parity error" },
		{ 0 }
	};
	char name[32];
	struct intr_info ii;
	bool fatal = false;

	if (is_t4(adap)) {
		snprintf(name, sizeof(name), "XGMAC_PORT%u_INT_CAUSE", port);
		ii.name = &name[0];
		ii.cause_reg = PORT_REG(port, A_XGMAC_PORT_INT_CAUSE);
		ii.enable_reg = PORT_REG(port, A_XGMAC_PORT_INT_EN);
		ii.fatal = F_TXFIFO_PRTY_ERR | F_RXFIFO_PRTY_ERR;
		ii.flags = 0;
		ii.details = mac_intr_details;
		ii.actions = NULL;
	} else {
		snprintf(name, sizeof(name), "MAC_PORT%u_INT_CAUSE", port);
		ii.name = &name[0];
		ii.cause_reg = T5_PORT_REG(port, A_MAC_PORT_INT_CAUSE);
		ii.enable_reg = T5_PORT_REG(port, A_MAC_PORT_INT_EN);
		ii.fatal = F_TXFIFO_PRTY_ERR | F_RXFIFO_PRTY_ERR;
		ii.flags = 0;
		ii.details = mac_intr_details;
		ii.actions = NULL;
	}
	fatal |= t4_handle_intr(adap, &ii, 0, verbose);

	if (chip_id(adap) >= CHELSIO_T5) {
		snprintf(name, sizeof(name), "MAC_PORT%u_PERR_INT_CAUSE", port);
		ii.name = &name[0];
		ii.cause_reg = T5_PORT_REG(port, A_MAC_PORT_PERR_INT_CAUSE);
		ii.enable_reg = T5_PORT_REG(port, A_MAC_PORT_PERR_INT_EN);
		ii.fatal = 0;
		ii.flags = 0;
		ii.details = NULL;
		ii.actions = NULL;
		fatal |= t4_handle_intr(adap, &ii, 0, verbose);
	}

	if (chip_id(adap) >= CHELSIO_T6) {
		snprintf(name, sizeof(name), "MAC_PORT%u_PERR_INT_CAUSE_100G", port);
		ii.name = &name[0];
		ii.cause_reg = T5_PORT_REG(port, A_MAC_PORT_PERR_INT_CAUSE_100G);
		ii.enable_reg = T5_PORT_REG(port, A_MAC_PORT_PERR_INT_EN_100G);
		ii.fatal = 0;
		ii.flags = 0;
		ii.details = NULL;
		ii.actions = NULL;
		fatal |= t4_handle_intr(adap, &ii, 0, verbose);
	}

	return (fatal);
}