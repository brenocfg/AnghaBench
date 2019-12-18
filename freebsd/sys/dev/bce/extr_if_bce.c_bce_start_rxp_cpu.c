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
struct cpu_reg {int state_value_clear; int mips_view_base; int /*<<< orphan*/  spad_base; int /*<<< orphan*/  bp; int /*<<< orphan*/  inst; int /*<<< orphan*/  pc; int /*<<< orphan*/  evmask; int /*<<< orphan*/  gpr0; int /*<<< orphan*/  state; int /*<<< orphan*/  mode_value_sstep; int /*<<< orphan*/  mode_value_halt; int /*<<< orphan*/  mode; } ;
struct bce_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCE_INFO_RESET ; 
 int /*<<< orphan*/  BCE_RXP_CPU_EVENT_MASK ; 
 int /*<<< orphan*/  BCE_RXP_CPU_HW_BREAKPOINT ; 
 int /*<<< orphan*/  BCE_RXP_CPU_INSTRUCTION ; 
 int /*<<< orphan*/  BCE_RXP_CPU_MODE ; 
 int /*<<< orphan*/  BCE_RXP_CPU_MODE_SOFT_HALT ; 
 int /*<<< orphan*/  BCE_RXP_CPU_MODE_STEP_ENA ; 
 int /*<<< orphan*/  BCE_RXP_CPU_PROGRAM_COUNTER ; 
 int /*<<< orphan*/  BCE_RXP_CPU_REG_FILE ; 
 int /*<<< orphan*/  BCE_RXP_CPU_STATE ; 
 int /*<<< orphan*/  BCE_RXP_SCRATCH ; 
 int /*<<< orphan*/  BCE_VERBOSE_RESET ; 
 int /*<<< orphan*/  DBENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBEXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBPRINT (struct bce_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bce_start_cpu (struct bce_softc*,struct cpu_reg*) ; 

__attribute__((used)) static void
bce_start_rxp_cpu(struct bce_softc *sc)
{
	struct cpu_reg cpu_reg;

	DBENTER(BCE_VERBOSE_RESET);

	cpu_reg.mode = BCE_RXP_CPU_MODE;
	cpu_reg.mode_value_halt = BCE_RXP_CPU_MODE_SOFT_HALT;
	cpu_reg.mode_value_sstep = BCE_RXP_CPU_MODE_STEP_ENA;
	cpu_reg.state = BCE_RXP_CPU_STATE;
	cpu_reg.state_value_clear = 0xffffff;
	cpu_reg.gpr0 = BCE_RXP_CPU_REG_FILE;
	cpu_reg.evmask = BCE_RXP_CPU_EVENT_MASK;
	cpu_reg.pc = BCE_RXP_CPU_PROGRAM_COUNTER;
	cpu_reg.inst = BCE_RXP_CPU_INSTRUCTION;
	cpu_reg.bp = BCE_RXP_CPU_HW_BREAKPOINT;
	cpu_reg.spad_base = BCE_RXP_SCRATCH;
	cpu_reg.mips_view_base = 0x8000000;

	DBPRINT(sc, BCE_INFO_RESET, "Starting RX firmware.\n");
	bce_start_cpu(sc, &cpu_reg);

	DBEXIT(BCE_VERBOSE_RESET);
}