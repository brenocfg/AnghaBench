#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int R_AX; int R_BL; int R_CX; int R_DX; int /*<<< orphan*/  R_DI; int /*<<< orphan*/  R_ES; } ;
typedef  TYPE_1__ x86regs_t ;
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  X86BIOS_PHYSTOOFF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X86BIOS_PHYSTOSEG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vesa_lock ; 
 int* vesa_palette ; 
 int /*<<< orphan*/  vesa_palette_offs ; 
 int /*<<< orphan*/  x86bios_init_regs (TYPE_1__*) ; 
 int /*<<< orphan*/  x86bios_intr (TYPE_1__*,int) ; 

__attribute__((used)) static int
vesa_bios_save_palette(int start, int colors, u_char *palette, int bits)
{
	x86regs_t regs;
	int i;

	x86bios_init_regs(&regs);
	regs.R_AX = 0x4f09;
	regs.R_BL = 1;
	regs.R_CX = colors;
	regs.R_DX = start;

	regs.R_ES = X86BIOS_PHYSTOSEG(vesa_palette_offs);
	regs.R_DI = X86BIOS_PHYSTOOFF(vesa_palette_offs);

	bits = 8 - bits;
	mtx_lock(&vesa_lock);
	x86bios_intr(&regs, 0x10);
	if (regs.R_AX != 0x004f) {
		mtx_unlock(&vesa_lock);
		return (1);
	}
	for (i = 0; i < colors; ++i) {
		palette[i * 3] = vesa_palette[i * 4 + 2] << bits;
		palette[i * 3 + 1] = vesa_palette[i * 4 + 1] << bits;
		palette[i * 3 + 2] = vesa_palette[i * 4] << bits;
	}
	mtx_unlock(&vesa_lock);

	return (0);
}