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
struct emu_sc_info {int dummy; } ;

/* Variables and functions */
 int EMU_SOLEH ; 
 int EMU_SOLEL ; 
 int /*<<< orphan*/  emu_wrptr (struct emu_sc_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
emu_vstop(struct emu_sc_info *sc, char channel, int enable)
{
	int reg;

	reg = (channel & 0x20) ? EMU_SOLEH : EMU_SOLEL;
	channel &= 0x1f;
	reg |= 1 << 24;
	reg |= channel << 16;
	emu_wrptr(sc, 0, reg, enable);
}