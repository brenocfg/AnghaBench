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
struct TYPE_2__ {int /*<<< orphan*/  r_addend; int /*<<< orphan*/  r_info; } ;
typedef  TYPE_1__ Elf64_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  ELF64_R_SYM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ELF64_R_TYPE (int /*<<< orphan*/ ) ; 
 int cmp_3way (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmp_rela(const void *a, const void *b)
{
	const Elf64_Rela *x = a, *y = b;
	int i;

	/* sort by type, symbol index and addend */
	i = cmp_3way(ELF64_R_TYPE(x->r_info), ELF64_R_TYPE(y->r_info));
	if (i == 0)
		i = cmp_3way(ELF64_R_SYM(x->r_info), ELF64_R_SYM(y->r_info));
	if (i == 0)
		i = cmp_3way(x->r_addend, y->r_addend);
	return i;
}