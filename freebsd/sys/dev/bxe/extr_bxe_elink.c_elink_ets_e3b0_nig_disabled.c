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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct elink_vars {int dummy; } ;
struct elink_params {scalar_t__ port; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CLIENT_CREDIT_MAP2_LSB ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CLIENT_CREDIT_MAP2_MSB ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CLIENT_IS_STRICT ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CLIENT_IS_SUBJECT2WFQ ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_0 ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_1 ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_2 ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_3 ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_4 ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_5 ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_6 ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_7 ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_8 ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_PRIORITY_CLIENT2_LSB ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_PRIORITY_CLIENT2_MSB ; 
 int /*<<< orphan*/  NIG_REG_P1_TX_ARB_CLIENT_CREDIT_MAP2_LSB ; 
 int /*<<< orphan*/  NIG_REG_P1_TX_ARB_CLIENT_CREDIT_MAP2_MSB ; 
 int /*<<< orphan*/  NIG_REG_P1_TX_ARB_CLIENT_IS_STRICT ; 
 int /*<<< orphan*/  NIG_REG_P1_TX_ARB_CLIENT_IS_SUBJECT2WFQ ; 
 int /*<<< orphan*/  NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_0 ; 
 int /*<<< orphan*/  NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_1 ; 
 int /*<<< orphan*/  NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_2 ; 
 int /*<<< orphan*/  NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_3 ; 
 int /*<<< orphan*/  NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_4 ; 
 int /*<<< orphan*/  NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_5 ; 
 int /*<<< orphan*/  NIG_REG_P1_TX_ARB_NUM_STRICT_ARB_SLOTS ; 
 int /*<<< orphan*/  NIG_REG_P1_TX_ARB_PRIORITY_CLIENT2_LSB ; 
 int /*<<< orphan*/  NIG_REG_P1_TX_ARB_PRIORITY_CLIENT2_MSB ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elink_ets_e3b0_set_credit_upper_bound_nig (struct elink_params const*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  elink_ets_get_min_w_val_nig (struct elink_vars const*) ; 

__attribute__((used)) static void elink_ets_e3b0_nig_disabled(const struct elink_params *params,
					const struct elink_vars *vars)
{
	struct bxe_softc *sc = params->sc;
	const uint8_t port = params->port;
	const uint32_t min_w_val = elink_ets_get_min_w_val_nig(vars);
	/* Mapping between entry  priority to client number (0,1,2 -debug and
	 * management clients, 3 - COS0 client, 4 - COS1, ... 8 -
	 * COS5)(HIGHEST) 4bits client num.TODO_ETS - Should be done by
	 * reset value or init tool
	 */
	if (port) {
		REG_WR(sc, NIG_REG_P1_TX_ARB_PRIORITY_CLIENT2_LSB, 0x543210);
		REG_WR(sc, NIG_REG_P1_TX_ARB_PRIORITY_CLIENT2_MSB, 0x0);
	} else {
		REG_WR(sc, NIG_REG_P0_TX_ARB_PRIORITY_CLIENT2_LSB, 0x76543210);
		REG_WR(sc, NIG_REG_P0_TX_ARB_PRIORITY_CLIENT2_MSB, 0x8);
	}
	/* For strict priority entries defines the number of consecutive
	 * slots for the highest priority.
	 */
	REG_WR(sc, (port) ? NIG_REG_P1_TX_ARB_NUM_STRICT_ARB_SLOTS :
		   NIG_REG_P1_TX_ARB_NUM_STRICT_ARB_SLOTS, 0x100);
	/* Mapping between the CREDIT_WEIGHT registers and actual client
	 * numbers
	 */
	if (port) {
		/*Port 1 has 6 COS*/
		REG_WR(sc, NIG_REG_P1_TX_ARB_CLIENT_CREDIT_MAP2_LSB, 0x210543);
		REG_WR(sc, NIG_REG_P1_TX_ARB_CLIENT_CREDIT_MAP2_MSB, 0x0);
	} else {
		/*Port 0 has 9 COS*/
		REG_WR(sc, NIG_REG_P0_TX_ARB_CLIENT_CREDIT_MAP2_LSB,
		       0x43210876);
		REG_WR(sc, NIG_REG_P0_TX_ARB_CLIENT_CREDIT_MAP2_MSB, 0x5);
	}

	/* Bitmap of 5bits length. Each bit specifies whether the entry behaves
	 * as strict.  Bits 0,1,2 - debug and management entries, 3 -
	 * COS0 entry, 4 - COS1 entry.
	 * COS1 | COS0 | DEBUG1 | DEBUG0 | MGMT
	 * bit4   bit3	  bit2   bit1	  bit0
	 * MCP and debug are strict
	 */
	if (port)
		REG_WR(sc, NIG_REG_P1_TX_ARB_CLIENT_IS_STRICT, 0x3f);
	else
		REG_WR(sc, NIG_REG_P0_TX_ARB_CLIENT_IS_STRICT, 0x1ff);
	/* defines which entries (clients) are subjected to WFQ arbitration */
	REG_WR(sc, (port) ? NIG_REG_P1_TX_ARB_CLIENT_IS_SUBJECT2WFQ :
		   NIG_REG_P0_TX_ARB_CLIENT_IS_SUBJECT2WFQ, 0);

	/* Please notice the register address are note continuous and a
	 * for here is note appropriate.In 2 port mode port0 only COS0-5
	 * can be used. DEBUG1,DEBUG1,MGMT are never used for WFQ* In 4
	 * port mode port1 only COS0-2 can be used. DEBUG1,DEBUG1,MGMT
	 * are never used for WFQ
	 */
	REG_WR(sc, (port) ? NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_0 :
		   NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_0, 0x0);
	REG_WR(sc, (port) ? NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_1 :
		   NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_1, 0x0);
	REG_WR(sc, (port) ? NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_2 :
		   NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_2, 0x0);
	REG_WR(sc, (port) ? NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_3 :
		   NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_3, 0x0);
	REG_WR(sc, (port) ? NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_4 :
		   NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_4, 0x0);
	REG_WR(sc, (port) ? NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_5 :
		   NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_5, 0x0);
	if (!port) {
		REG_WR(sc, NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_6, 0x0);
		REG_WR(sc, NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_7, 0x0);
		REG_WR(sc, NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_8, 0x0);
	}

	elink_ets_e3b0_set_credit_upper_bound_nig(params, min_w_val);
}