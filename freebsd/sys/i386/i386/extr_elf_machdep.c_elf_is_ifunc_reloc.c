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
typedef  int /*<<< orphan*/  Elf_Size ;

/* Variables and functions */
 scalar_t__ ELF_R_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ R_386_IRELATIVE ; 

bool
elf_is_ifunc_reloc(Elf_Size r_info)
{

	return (ELF_R_TYPE(r_info) == R_386_IRELATIVE);
}