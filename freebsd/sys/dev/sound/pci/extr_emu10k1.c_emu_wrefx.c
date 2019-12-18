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
struct sc_info {scalar_t__ audigy; } ;

/* Variables and functions */
 scalar_t__ EMU_A_MICROCODEBASE ; 
 scalar_t__ EMU_MICROCODEBASE ; 
 int /*<<< orphan*/  emu_wrptr (struct sc_info*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void
emu_wrefx(struct sc_info *sc, unsigned int pc, unsigned int data)
{
	pc += sc->audigy ? EMU_A_MICROCODEBASE : EMU_MICROCODEBASE;
	emu_wrptr(sc, 0, pc, data);
}