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
typedef  int /*<<< orphan*/  u32 ;
struct cpu_reg {int /*<<< orphan*/  state_value_clear; int /*<<< orphan*/  state; int /*<<< orphan*/  mode; int /*<<< orphan*/  mode_value_halt; } ;
struct bce_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCE_VERBOSE_RESET ; 
 int /*<<< orphan*/  DBENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBEXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RD_IND (struct bce_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR_IND (struct bce_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bce_halt_cpu(struct bce_softc *sc, struct cpu_reg *cpu_reg)
{
	u32 val;

	DBENTER(BCE_VERBOSE_RESET);

	/* Halt the CPU. */
	val = REG_RD_IND(sc, cpu_reg->mode);
	val |= cpu_reg->mode_value_halt;
	REG_WR_IND(sc, cpu_reg->mode, val);
	REG_WR_IND(sc, cpu_reg->state, cpu_reg->state_value_clear);

	DBEXIT(BCE_VERBOSE_RESET);
}