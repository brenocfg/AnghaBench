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
struct module {int dummy; } ;
typedef  int Elf_Addr ;

/* Variables and functions */

__attribute__((used)) static int apply_r_riscv_pcrel_lo12_i_rela(struct module *me, u32 *location,
					   Elf_Addr v)
{
	/*
	 * v is the lo12 value to fill. It is calculated before calling this
	 * handler.
	 */
	*location = (*location & 0xfffff) | ((v & 0xfff) << 20);
	return 0;
}