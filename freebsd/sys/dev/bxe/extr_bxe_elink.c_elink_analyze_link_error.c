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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct elink_vars {int phy_flags; int link_up; int link_status; int /*<<< orphan*/  periodic_flags; } ;
struct elink_params {int port; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P3 (struct bxe_softc*,char*,int,int,int) ; 
 int ELINK_LED_MODE_OFF ; 
 int ELINK_LED_MODE_OPER ; 
 int /*<<< orphan*/  ELINK_PERIODIC_FLAGS_LINK_EVENT ; 
 int /*<<< orphan*/  ELINK_SPEED_10000 ; 
 int LINK_STATUS_LINK_UP ; 
 scalar_t__ NIG_REG_EGRESS_DRAIN0_MODE ; 
#define  PHY_HALF_OPEN_CONN_FLAG 129 
 int PHY_PHYSICAL_LINK_FLAG ; 
#define  PHY_SFP_TX_FAULT_FLAG 128 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  elink_cb_notify_link_changed (struct bxe_softc*) ; 
 int /*<<< orphan*/  elink_set_led (struct elink_params*,struct elink_vars*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_sync_link (struct elink_params*,struct elink_vars*) ; 
 int /*<<< orphan*/  elink_update_mng (struct elink_params*,int) ; 

__attribute__((used)) static uint8_t elink_analyze_link_error(struct elink_params *params,
				    struct elink_vars *vars, uint32_t status,
				    uint32_t phy_flag, uint32_t link_flag, uint8_t notify)
{
	struct bxe_softc *sc = params->sc;
	/* Compare new value with previous value */
	uint8_t led_mode;
	uint32_t old_status = (vars->phy_flags & phy_flag) ? 1 : 0;

	if ((status ^ old_status) == 0)
		return 0;

	/* If values differ */
	switch (phy_flag) {
	case PHY_HALF_OPEN_CONN_FLAG:
		ELINK_DEBUG_P0(sc, "Analyze Remote Fault\n");
		break;
	case PHY_SFP_TX_FAULT_FLAG:
		ELINK_DEBUG_P0(sc, "Analyze TX Fault\n");
		break;
	default:
		ELINK_DEBUG_P0(sc, "Analyze UNKNOWN\n");
	}
	ELINK_DEBUG_P3(sc, "Link changed:[%x %x]->%x\n", vars->link_up,
	   old_status, status);

	/* Do not touch the link in case physical link down */
	if ((vars->phy_flags & PHY_PHYSICAL_LINK_FLAG) == 0)
		return 1;

	/* a. Update shmem->link_status accordingly
	 * b. Update elink_vars->link_up
	 */
	if (status) {
		vars->link_status &= ~LINK_STATUS_LINK_UP;
		vars->link_status |= link_flag;
		vars->link_up = 0;
		vars->phy_flags |= phy_flag;

		/* activate nig drain */
		REG_WR(sc, NIG_REG_EGRESS_DRAIN0_MODE + params->port*4, 1);
		/* Set LED mode to off since the PHY doesn't know about these
		 * errors
		 */
		led_mode = ELINK_LED_MODE_OFF;
	} else {
		vars->link_status |= LINK_STATUS_LINK_UP;
		vars->link_status &= ~link_flag;
		vars->link_up = 1;
		vars->phy_flags &= ~phy_flag;
		led_mode = ELINK_LED_MODE_OPER;

		/* Clear nig drain */
		REG_WR(sc, NIG_REG_EGRESS_DRAIN0_MODE + params->port*4, 0);
	}
	elink_sync_link(params, vars);
	/* Update the LED according to the link state */
	elink_set_led(params, vars, led_mode, ELINK_SPEED_10000);

	/* Update link status in the shared memory */
	elink_update_mng(params, vars->link_status);

	/* C. Trigger General Attention */
	vars->periodic_flags |= ELINK_PERIODIC_FLAGS_LINK_EVENT;
	if (notify)
		elink_cb_notify_link_changed(sc);

	return 1;
}