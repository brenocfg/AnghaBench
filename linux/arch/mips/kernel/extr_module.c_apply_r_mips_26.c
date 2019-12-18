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
typedef  int Elf_Addr ;

/* Variables and functions */
 int ENOEXEC ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apply_r_mips_26(struct module *me, u32 *location,
			   u32 base, Elf_Addr v, bool rela)
{
	if (v % 4) {
		pr_err("module %s: dangerous R_MIPS_26 relocation\n",
		       me->name);
		return -ENOEXEC;
	}

	if ((v & 0xf0000000) != (((unsigned long)location + 4) & 0xf0000000)) {
		pr_err("module %s: relocation overflow\n",
		       me->name);
		return -ENOEXEC;
	}

	*location = (*location & ~0x03ffffff) |
		    ((base + (v >> 2)) & 0x03ffffff);

	return 0;
}