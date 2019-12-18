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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int mode; scalar_t__ R_CX; int R_DI; int /*<<< orphan*/  R_AX; int /*<<< orphan*/  R_ES; int /*<<< orphan*/  R_EAX; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */
 scalar_t__ ACCESS_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_DF ; 
 int /*<<< orphan*/  F_ZF ; 
 int SYSMODE_PREFIX_DATA ; 
 int SYSMODE_PREFIX_REPE ; 
 int SYSMODE_PREFIX_REPNE ; 
 int /*<<< orphan*/  cmp_long (struct x86emu*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cmp_word (struct x86emu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fetch_long (struct x86emu*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ fetch_word (struct x86emu*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
x86emuOp_scas_word(struct x86emu *emu)
{
	int inc;
	uint32_t val;

	if (emu->x86.mode & SYSMODE_PREFIX_DATA)
		inc = 4;
	else
		inc = 2;

	if (ACCESS_FLAG(F_DF))	/* down */
		inc = -inc;

	if (emu->x86.mode & SYSMODE_PREFIX_REPE) {
		/* REPE  */
		/* move them until CX is ZERO. */
		while (emu->x86.R_CX != 0) {
			if (emu->x86.mode & SYSMODE_PREFIX_DATA) {
				val = fetch_long(emu, emu->x86.R_ES,
				    emu->x86.R_DI);
				cmp_long(emu, emu->x86.R_EAX, val);
			} else {
				val = fetch_word(emu, emu->x86.R_ES,
				    emu->x86.R_DI);
				cmp_word(emu, emu->x86.R_AX, (uint16_t) val);
			}
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
			if (emu->x86.mode & SYSMODE_PREFIX_DATA) {
				val = fetch_long(emu, emu->x86.R_ES,
				    emu->x86.R_DI);
				cmp_long(emu, emu->x86.R_EAX, val);
			} else {
				val = fetch_word(emu, emu->x86.R_ES,
				    emu->x86.R_DI);
				cmp_word(emu, emu->x86.R_AX, (uint16_t) val);
			}
			emu->x86.R_CX -= 1;
			emu->x86.R_DI += inc;
			if (ACCESS_FLAG(F_ZF))
				break;	/* zero flag set means equal */
		}
		emu->x86.mode &= ~SYSMODE_PREFIX_REPNE;
	} else {
		if (emu->x86.mode & SYSMODE_PREFIX_DATA) {
			val = fetch_long(emu, emu->x86.R_ES, emu->x86.R_DI);
			cmp_long(emu, emu->x86.R_EAX, val);
		} else {
			val = fetch_word(emu, emu->x86.R_ES, emu->x86.R_DI);
			cmp_word(emu, emu->x86.R_AX, (uint16_t) val);
		}
		emu->x86.R_DI += inc;
	}
}