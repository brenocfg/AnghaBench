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
typedef  int u32 ;
struct e1000_mac_info {int serdes_link_state; int txcw; void* serdes_has_link; } ;
struct e1000_hw {struct e1000_mac_info mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int AN_RETRY_COUNT ; 
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  E1000_CTRL ; 
 int E1000_CTRL_FD ; 
 int E1000_CTRL_SLU ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_RXCW ; 
 int E1000_RXCW_C ; 
 int E1000_RXCW_IV ; 
 int E1000_RXCW_SYNCH ; 
 int /*<<< orphan*/  E1000_STATUS ; 
 int E1000_STATUS_LU ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_TXCW ; 
 int E1000_TXCW_ANE ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  e1000_config_fc_after_link_up_generic (struct e1000_hw*) ; 
#define  e1000_serdes_link_autoneg_complete 131 
#define  e1000_serdes_link_autoneg_progress 130 
#define  e1000_serdes_link_down 129 
#define  e1000_serdes_link_forced_up 128 
 int /*<<< orphan*/  usec_delay (int) ; 

__attribute__((used)) static s32 e1000_check_for_serdes_link_82571(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	u32 rxcw;
	u32 ctrl;
	u32 status;
	u32 txcw;
	u32 i;
	s32 ret_val = E1000_SUCCESS;

	DEBUGFUNC("e1000_check_for_serdes_link_82571");

	ctrl = E1000_READ_REG(hw, E1000_CTRL);
	status = E1000_READ_REG(hw, E1000_STATUS);
	E1000_READ_REG(hw, E1000_RXCW);
	/* SYNCH bit and IV bit are sticky */
	usec_delay(10);
	rxcw = E1000_READ_REG(hw, E1000_RXCW);

	if ((rxcw & E1000_RXCW_SYNCH) && !(rxcw & E1000_RXCW_IV)) {
		/* Receiver is synchronized with no invalid bits.  */
		switch (mac->serdes_link_state) {
		case e1000_serdes_link_autoneg_complete:
			if (!(status & E1000_STATUS_LU)) {
				/* We have lost link, retry autoneg before
				 * reporting link failure
				 */
				mac->serdes_link_state =
				    e1000_serdes_link_autoneg_progress;
				mac->serdes_has_link = FALSE;
				DEBUGOUT("AN_UP     -> AN_PROG\n");
			} else {
				mac->serdes_has_link = TRUE;
			}
			break;

		case e1000_serdes_link_forced_up:
			/* If we are receiving /C/ ordered sets, re-enable
			 * auto-negotiation in the TXCW register and disable
			 * forced link in the Device Control register in an
			 * attempt to auto-negotiate with our link partner.
			 */
			if (rxcw & E1000_RXCW_C) {
				/* Enable autoneg, and unforce link up */
				E1000_WRITE_REG(hw, E1000_TXCW, mac->txcw);
				E1000_WRITE_REG(hw, E1000_CTRL,
				    (ctrl & ~E1000_CTRL_SLU));
				mac->serdes_link_state =
				    e1000_serdes_link_autoneg_progress;
				mac->serdes_has_link = FALSE;
				DEBUGOUT("FORCED_UP -> AN_PROG\n");
			} else {
				mac->serdes_has_link = TRUE;
			}
			break;

		case e1000_serdes_link_autoneg_progress:
			if (rxcw & E1000_RXCW_C) {
				/* We received /C/ ordered sets, meaning the
				 * link partner has autonegotiated, and we can
				 * trust the Link Up (LU) status bit.
				 */
				if (status & E1000_STATUS_LU) {
					mac->serdes_link_state =
					    e1000_serdes_link_autoneg_complete;
					DEBUGOUT("AN_PROG   -> AN_UP\n");
					mac->serdes_has_link = TRUE;
				} else {
					/* Autoneg completed, but failed. */
					mac->serdes_link_state =
					    e1000_serdes_link_down;
					DEBUGOUT("AN_PROG   -> DOWN\n");
				}
			} else {
				/* The link partner did not autoneg.
				 * Force link up and full duplex, and change
				 * state to forced.
				 */
				E1000_WRITE_REG(hw, E1000_TXCW,
				(mac->txcw & ~E1000_TXCW_ANE));
				ctrl |= (E1000_CTRL_SLU | E1000_CTRL_FD);
				E1000_WRITE_REG(hw, E1000_CTRL, ctrl);

				/* Configure Flow Control after link up. */
				ret_val =
				    e1000_config_fc_after_link_up_generic(hw);
				if (ret_val) {
					DEBUGOUT("Error config flow control\n");
					break;
				}
				mac->serdes_link_state =
						e1000_serdes_link_forced_up;
				mac->serdes_has_link = TRUE;
				DEBUGOUT("AN_PROG   -> FORCED_UP\n");
			}
			break;

		case e1000_serdes_link_down:
		default:
			/* The link was down but the receiver has now gained
			 * valid sync, so lets see if we can bring the link
			 * up.
			 */
			E1000_WRITE_REG(hw, E1000_TXCW, mac->txcw);
			E1000_WRITE_REG(hw, E1000_CTRL, (ctrl &
					~E1000_CTRL_SLU));
			mac->serdes_link_state =
					e1000_serdes_link_autoneg_progress;
			mac->serdes_has_link = FALSE;
			DEBUGOUT("DOWN      -> AN_PROG\n");
			break;
		}
	} else {
		if (!(rxcw & E1000_RXCW_SYNCH)) {
			mac->serdes_has_link = FALSE;
			mac->serdes_link_state = e1000_serdes_link_down;
			DEBUGOUT("ANYSTATE  -> DOWN\n");
		} else {
			/* Check several times, if SYNCH bit and CONFIG
			 * bit both are consistently 1 then simply ignore
			 * the IV bit and restart Autoneg
			 */
			for (i = 0; i < AN_RETRY_COUNT; i++) {
				usec_delay(10);
				rxcw = E1000_READ_REG(hw, E1000_RXCW);
				if ((rxcw & E1000_RXCW_SYNCH) &&
				    (rxcw & E1000_RXCW_C))
					continue;

				if (rxcw & E1000_RXCW_IV) {
					mac->serdes_has_link = FALSE;
					mac->serdes_link_state =
							e1000_serdes_link_down;
					DEBUGOUT("ANYSTATE  -> DOWN\n");
					break;
				}
			}

			if (i == AN_RETRY_COUNT) {
				txcw = E1000_READ_REG(hw, E1000_TXCW);
				txcw |= E1000_TXCW_ANE;
				E1000_WRITE_REG(hw, E1000_TXCW, txcw);
				mac->serdes_link_state =
					e1000_serdes_link_autoneg_progress;
				mac->serdes_has_link = FALSE;
				DEBUGOUT("ANYSTATE  -> AN_PROG\n");
			}
		}
	}

	return ret_val;
}