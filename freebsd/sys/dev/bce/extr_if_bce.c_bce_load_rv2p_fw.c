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
typedef  scalar_t__ u32 ;
struct bce_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCE_RV2P_COMMAND ; 
 scalar_t__ BCE_RV2P_COMMAND_PROC1_RESET ; 
 scalar_t__ BCE_RV2P_COMMAND_PROC2_RESET ; 
 int /*<<< orphan*/  BCE_RV2P_INSTR_HIGH ; 
 int /*<<< orphan*/  BCE_RV2P_INSTR_LOW ; 
 int /*<<< orphan*/  BCE_RV2P_PROC1_ADDR_CMD ; 
 int BCE_RV2P_PROC1_ADDR_CMD_RDWR ; 
 int /*<<< orphan*/  BCE_RV2P_PROC2_ADDR_CMD ; 
 int BCE_RV2P_PROC2_ADDR_CMD_RDWR ; 
 int /*<<< orphan*/  BCE_RV2P_PROC2_CHG_MAX_BD_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCE_VERBOSE_RESET ; 
 int /*<<< orphan*/  DBENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBEXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bce_softc*,int /*<<< orphan*/ ,scalar_t__ const) ; 
 scalar_t__ RV2P_PROC1 ; 
 scalar_t__ RV2P_PROC2 ; 
 int /*<<< orphan*/  USABLE_RX_BD_PER_PAGE ; 

__attribute__((used)) static void
bce_load_rv2p_fw(struct bce_softc *sc, const u32 *rv2p_code,
	u32 rv2p_code_len, u32 rv2p_proc)
{
	int i;
	u32 val;

	DBENTER(BCE_VERBOSE_RESET);

	/* Set the page size used by RV2P. */
	if (rv2p_proc == RV2P_PROC2) {
		BCE_RV2P_PROC2_CHG_MAX_BD_PAGE(USABLE_RX_BD_PER_PAGE);
	}

	for (i = 0; i < rv2p_code_len; i += 8) {
		REG_WR(sc, BCE_RV2P_INSTR_HIGH, *rv2p_code);
		rv2p_code++;
		REG_WR(sc, BCE_RV2P_INSTR_LOW, *rv2p_code);
		rv2p_code++;

		if (rv2p_proc == RV2P_PROC1) {
			val = (i / 8) | BCE_RV2P_PROC1_ADDR_CMD_RDWR;
			REG_WR(sc, BCE_RV2P_PROC1_ADDR_CMD, val);
		}
		else {
			val = (i / 8) | BCE_RV2P_PROC2_ADDR_CMD_RDWR;
			REG_WR(sc, BCE_RV2P_PROC2_ADDR_CMD, val);
		}
	}

	/* Reset the processor, un-stall is done later. */
	if (rv2p_proc == RV2P_PROC1) {
		REG_WR(sc, BCE_RV2P_COMMAND, BCE_RV2P_COMMAND_PROC1_RESET);
	}
	else {
		REG_WR(sc, BCE_RV2P_COMMAND, BCE_RV2P_COMMAND_PROC2_RESET);
	}

	DBEXIT(BCE_VERBOSE_RESET);
}