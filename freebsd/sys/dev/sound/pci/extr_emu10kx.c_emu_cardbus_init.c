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
 int /*<<< orphan*/  emu_wr_cbptr (struct emu_sc_info*,int) ; 

__attribute__((used)) static int
emu_cardbus_init(struct emu_sc_info *sc)
{

	/*
	 * XXX May not need this if we have EMU_IPR3 handler.
	 * Is it a real init calls, or EMU_IPR3 interrupt acknowledgments?
	 * Looks much like "(data << 16) | register".
	 */
	emu_wr_cbptr(sc, (0x00d0 << 16) | 0x0000);
	emu_wr_cbptr(sc, (0x00d0 << 16) | 0x0001);
	emu_wr_cbptr(sc, (0x00d0 << 16) | 0x005f);
	emu_wr_cbptr(sc, (0x00d0 << 16) | 0x007f);

	emu_wr_cbptr(sc, (0x0090 << 16) | 0x007f);

	return (0);
}