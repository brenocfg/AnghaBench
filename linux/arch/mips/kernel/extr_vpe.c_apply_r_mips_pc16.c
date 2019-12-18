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
typedef  int uint32_t ;
struct module {int dummy; } ;
typedef  scalar_t__ Elf32_Addr ;

/* Variables and functions */
 int ENOEXEC ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static int apply_r_mips_pc16(struct module *me, uint32_t *location,
			     Elf32_Addr v)
{
	int rel;
	rel = (((unsigned int)v - (unsigned int)location));
	rel >>= 2; /* because the offset is in _instructions_ not bytes. */
	rel -= 1;  /* and one instruction less due to the branch delay slot. */

	if ((rel > 32768) || (rel < -32768)) {
		pr_debug("VPE loader: apply_r_mips_pc16: relative address out of range 0x%x\n",
			 rel);
		return -ENOEXEC;
	}

	*location = (*location & 0xffff0000) | (rel & 0xffff);

	return 0;
}