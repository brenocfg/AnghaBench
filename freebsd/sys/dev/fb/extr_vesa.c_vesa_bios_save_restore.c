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
struct TYPE_4__ {int R_AX; int R_DL; int /*<<< orphan*/  R_BX; int /*<<< orphan*/  R_ES; int /*<<< orphan*/  R_CX; } ;
typedef  TYPE_1__ x86regs_t ;

/* Variables and functions */
#define  STATE_LOAD 129 
#define  STATE_SAVE 128 
 int /*<<< orphan*/  X86BIOS_PHYSTOOFF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X86BIOS_PHYSTOSEG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vesa_lock ; 
 int /*<<< orphan*/  vesa_state ; 
 void* vesa_state_buf ; 
 int /*<<< orphan*/  vesa_state_buf_offs ; 
 int /*<<< orphan*/  vesa_state_buf_size ; 
 int /*<<< orphan*/  x86bios_init_regs (TYPE_1__*) ; 
 int /*<<< orphan*/  x86bios_intr (TYPE_1__*,int) ; 

__attribute__((used)) static int
vesa_bios_save_restore(int code, void *p)
{
	x86regs_t regs;

	if (code != STATE_SAVE && code != STATE_LOAD)
		return (1);

	x86bios_init_regs(&regs);
	regs.R_AX = 0x4f04;
	regs.R_DL = code;
	regs.R_CX = vesa_state;

	regs.R_ES = X86BIOS_PHYSTOSEG(vesa_state_buf_offs);
	regs.R_BX = X86BIOS_PHYSTOOFF(vesa_state_buf_offs);

	mtx_lock(&vesa_lock);
	switch (code) {
	case STATE_SAVE:
		x86bios_intr(&regs, 0x10);
		if (regs.R_AX == 0x004f)
			bcopy(vesa_state_buf, p, vesa_state_buf_size);
		break;
	case STATE_LOAD:
		bcopy(p, vesa_state_buf, vesa_state_buf_size);
		x86bios_intr(&regs, 0x10);
		break;
	}
	mtx_unlock(&vesa_lock);

	return (regs.R_AX != 0x004f);
}