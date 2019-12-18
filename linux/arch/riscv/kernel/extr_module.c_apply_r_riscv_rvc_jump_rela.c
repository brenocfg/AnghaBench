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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct module {int dummy; } ;
typedef  int ptrdiff_t ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */

__attribute__((used)) static int apply_r_riscv_rvc_jump_rela(struct module *me, u32 *location,
				       Elf_Addr v)
{
	ptrdiff_t offset = (void *)v - (void *)location;
	u16 imm11 = (offset & 0x800) << (12 - 11);
	u16 imm10 = (offset & 0x400) >> (10 - 8);
	u16 imm9_8 = (offset & 0x300) << (12 - 11);
	u16 imm7 = (offset & 0x80) >> (7 - 6);
	u16 imm6 = (offset & 0x40) << (12 - 11);
	u16 imm5 = (offset & 0x20) >> (5 - 2);
	u16 imm4 = (offset & 0x10) << (12 - 5);
	u16 imm3_1 = (offset & 0xe) << (12 - 10);

	*(u16 *)location = (*(u16 *)location & 0xe003) |
		    imm11 | imm10 | imm9_8 | imm7 | imm6 | imm5 | imm4 | imm3_1;
	return 0;
}