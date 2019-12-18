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
typedef  int u_int32_t ;
struct sc_info {int addrmask; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU_DATA ; 
 int /*<<< orphan*/  EMU_PTR ; 
 int EMU_PTR_CHNO_MASK ; 
 int emu_rd (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emu_wr (struct sc_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static u_int32_t
emu_rdptr(struct sc_info *sc, int chn, int reg)
{
	u_int32_t ptr, val, mask, size, offset;

	ptr = ((reg << 16) & sc->addrmask) | (chn & EMU_PTR_CHNO_MASK);
	emu_wr(sc, EMU_PTR, ptr, 4);
	val = emu_rd(sc, EMU_DATA, 4);
	if (reg & 0xff000000) {
		size = (reg >> 24) & 0x3f;
		offset = (reg >> 16) & 0x1f;
		mask = ((1 << size) - 1) << offset;
		val &= mask;
		val >>= offset;
	}
	return val;
}