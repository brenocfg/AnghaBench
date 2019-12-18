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
typedef  int u32 ;
struct module {int /*<<< orphan*/  name; } ;
typedef  int s32 ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CMODEL_MEDLOW ; 
 int EINVAL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,long long,int*) ; 

__attribute__((used)) static int apply_r_riscv_hi20_rela(struct module *me, u32 *location,
				   Elf_Addr v)
{
	s32 hi20;

	if (IS_ENABLED(CONFIG_CMODEL_MEDLOW)) {
		pr_err(
		  "%s: target %016llx can not be addressed by the 32-bit offset from PC = %p\n",
		  me->name, (long long)v, location);
		return -EINVAL;
	}

	hi20 = ((s32)v + 0x800) & 0xfffff000;
	*location = (*location & 0xfff) | hi20;
	return 0;
}