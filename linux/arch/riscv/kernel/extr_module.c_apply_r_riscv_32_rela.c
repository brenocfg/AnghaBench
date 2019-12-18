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
typedef  scalar_t__ u32 ;
struct module {int /*<<< orphan*/  name; } ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,long long) ; 

__attribute__((used)) static int apply_r_riscv_32_rela(struct module *me, u32 *location, Elf_Addr v)
{
	if (v != (u32)v) {
		pr_err("%s: value %016llx out of range for 32-bit field\n",
		       me->name, (long long)v);
		return -EINVAL;
	}
	*location = v;
	return 0;
}