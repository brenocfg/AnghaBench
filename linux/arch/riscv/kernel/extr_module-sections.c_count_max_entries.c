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
struct TYPE_4__ {int /*<<< orphan*/  r_info; } ;
typedef  TYPE_1__ Elf_Rela ;

/* Variables and functions */
 unsigned int ELF_RISCV_R_TYPE (int /*<<< orphan*/ ) ; 
 unsigned int R_RISCV_CALL_PLT ; 
 unsigned int R_RISCV_GOT_HI20 ; 
 int /*<<< orphan*/  duplicate_rela (TYPE_1__*,unsigned int) ; 

__attribute__((used)) static void count_max_entries(Elf_Rela *relas, int num,
			      unsigned int *plts, unsigned int *gots)
{
	unsigned int type, i;

	for (i = 0; i < num; i++) {
		type = ELF_RISCV_R_TYPE(relas[i].r_info);
		if (type == R_RISCV_CALL_PLT) {
			if (!duplicate_rela(relas, i))
				(*plts)++;
		} else if (type == R_RISCV_GOT_HI20) {
			if (!duplicate_rela(relas, i))
				(*gots)++;
		}
	}
}