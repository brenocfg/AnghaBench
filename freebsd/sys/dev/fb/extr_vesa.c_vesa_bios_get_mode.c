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
struct TYPE_4__ {int R_AX; int R_CX; int /*<<< orphan*/  R_DI; int /*<<< orphan*/  R_ES; } ;
typedef  TYPE_1__ x86regs_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct vesa_mode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86BIOS_PHYSTOOFF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X86BIOS_PHYSTOSEG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (void*,struct vesa_mode*,int) ; 
 void* x86bios_alloc (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  x86bios_free (void*,int) ; 
 int /*<<< orphan*/  x86bios_init_regs (TYPE_1__*) ; 
 int /*<<< orphan*/  x86bios_intr (TYPE_1__*,int) ; 

__attribute__((used)) static int
vesa_bios_get_mode(int mode, struct vesa_mode *vmode, int flags)
{
	x86regs_t regs;
	uint32_t offs;
	void *buf;

	buf = x86bios_alloc(&offs, sizeof(*vmode), flags);
	if (buf == NULL)
		return (1);

	x86bios_init_regs(&regs);
	regs.R_AX = 0x4f01;
	regs.R_CX = mode;

	regs.R_ES = X86BIOS_PHYSTOSEG(offs);
	regs.R_DI = X86BIOS_PHYSTOOFF(offs);

	x86bios_intr(&regs, 0x10);

	if (regs.R_AX != 0x004f) {
		x86bios_free(buf, sizeof(*vmode));
		return (1);
	}

	bcopy(buf, vmode, sizeof(*vmode));
	x86bios_free(buf, sizeof(*vmode));

	return (0);
}