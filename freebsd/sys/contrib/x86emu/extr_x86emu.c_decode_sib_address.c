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
typedef  int uint32_t ;
struct TYPE_2__ {int R_EAX; int R_ECX; int R_EDX; int R_EBX; int R_ESP; int R_EBP; int R_ESI; int R_EDI; int /*<<< orphan*/  mode; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYSMODE_SEG_DS_SS ; 
 int fetch_long_imm (struct x86emu*) ; 

__attribute__((used)) static uint32_t 
decode_sib_address(struct x86emu *emu, int sib, int mod)
{
	uint32_t base = 0, i = 0, scale = 1;

	switch (sib & 0x07) {
	case 0:
		base = emu->x86.R_EAX;
		break;
	case 1:
		base = emu->x86.R_ECX;

		break;
	case 2:
		base = emu->x86.R_EDX;
		break;
	case 3:
		base = emu->x86.R_EBX;
		break;
	case 4:
		base = emu->x86.R_ESP;
		emu->x86.mode |= SYSMODE_SEG_DS_SS;
		break;
	case 5:
		if (mod == 0) {
			base = fetch_long_imm(emu);
		} else {
			base = emu->x86.R_EBP;
			emu->x86.mode |= SYSMODE_SEG_DS_SS;
		}
		break;
	case 6:
		base = emu->x86.R_ESI;
		break;
	case 7:
		base = emu->x86.R_EDI;
		break;
	}
	switch ((sib >> 3) & 0x07) {
	case 0:
		i = emu->x86.R_EAX;
		break;
	case 1:
		i = emu->x86.R_ECX;
		break;
	case 2:
		i = emu->x86.R_EDX;
		break;
	case 3:
		i = emu->x86.R_EBX;
		break;
	case 4:
		i = 0;
		break;
	case 5:
		i = emu->x86.R_EBP;
		break;
	case 6:
		i = emu->x86.R_ESI;
		break;
	case 7:
		i = emu->x86.R_EDI;
		break;
	}
	scale = 1 << ((sib >> 6) & 0x03);
	return base + (i * scale);
}