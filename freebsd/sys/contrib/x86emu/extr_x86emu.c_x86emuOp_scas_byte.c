#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int mode; scalar_t__ R_CX; int R_DI; int /*<<< orphan*/  R_AL; int /*<<< orphan*/  R_ES; } ;
struct x86emu {TYPE_1__ x86; } ;
typedef  int /*<<< orphan*/  int8_t ;

/* Variables and functions */
 scalar_t__ ACCESS_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_DF ; 
 int /*<<< orphan*/  F_ZF ; 
 int SYSMODE_PREFIX_REPE ; 
 int SYSMODE_PREFIX_REPNE ; 
 int /*<<< orphan*/  cmp_byte (struct x86emu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fetch_byte (struct x86emu*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
x86emuOp_scas_byte(struct x86emu *emu)
{
	int8_t val2;
	int inc;

	if (ACCESS_FLAG(F_DF))	/* down */
		inc = -1;
	else
		inc = 1;
	if (emu->x86.mode & SYSMODE_PREFIX_REPE) {
		/* REPE  */
		/* move them until CX is ZERO. */
		while (emu->x86.R_CX != 0) {
			val2 = fetch_byte(emu, emu->x86.R_ES, emu->x86.R_DI);
			cmp_byte(emu, emu->x86.R_AL, val2);
			emu->x86.R_CX -= 1;
			emu->x86.R_DI += inc;
			if (ACCESS_FLAG(F_ZF) == 0)
				break;
		}
		emu->x86.mode &= ~SYSMODE_PREFIX_REPE;
	} else if (emu->x86.mode & SYSMODE_PREFIX_REPNE) {
		/* REPNE  */
		/* move them until CX is ZERO. */
		while (emu->x86.R_CX != 0) {
			val2 = fetch_byte(emu, emu->x86.R_ES, emu->x86.R_DI);
			cmp_byte(emu, emu->x86.R_AL, val2);
			emu->x86.R_CX -= 1;
			emu->x86.R_DI += inc;
			if (ACCESS_FLAG(F_ZF))
				break;	/* zero flag set means equal */
		}
		emu->x86.mode &= ~SYSMODE_PREFIX_REPNE;
	} else {
		val2 = fetch_byte(emu, emu->x86.R_ES, emu->x86.R_DI);
		cmp_byte(emu, emu->x86.R_AL, val2);
		emu->x86.R_DI += inc;
	}
}