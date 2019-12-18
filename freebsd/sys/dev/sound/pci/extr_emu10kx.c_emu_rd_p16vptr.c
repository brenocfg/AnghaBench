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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct emu_sc_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU_A2_PTR ; 
 int /*<<< orphan*/  EMU_DATA2 ; 
 int /*<<< orphan*/  EMU_RWLOCK () ; 
 int /*<<< orphan*/  EMU_RWUNLOCK () ; 
 int /*<<< orphan*/  emu_rd_nolock (struct emu_sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emu_wr_nolock (struct emu_sc_info*,int /*<<< orphan*/ ,int,int) ; 

uint32_t
emu_rd_p16vptr(struct emu_sc_info *sc, uint16_t chn, uint16_t reg)
{
	uint32_t val;

	/* XXX separate lock? */
	EMU_RWLOCK();
	emu_wr_nolock(sc, EMU_A2_PTR, (reg << 16) | chn, 4);
	val = emu_rd_nolock(sc, EMU_DATA2, 4);

	EMU_RWUNLOCK();

	return (val);
}