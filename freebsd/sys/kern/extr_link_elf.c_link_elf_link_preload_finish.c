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
typedef  scalar_t__ linker_file_t ;
typedef  scalar_t__ elf_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  VM_PROT_NONE ; 
 int link_elf_link_common_finish (scalar_t__) ; 
 int /*<<< orphan*/  link_elf_preload_parse_symbols (scalar_t__) ; 
 int preload_protect (scalar_t__,int /*<<< orphan*/ ) ; 
 int relocate_file (scalar_t__) ; 

__attribute__((used)) static int
link_elf_link_preload_finish(linker_file_t lf)
{
	elf_file_t ef;
	int error;

	ef = (elf_file_t) lf;
	error = relocate_file(ef);
	if (error == 0)
		error = preload_protect(ef, VM_PROT_NONE);
	if (error != 0)
		return (error);
	(void)link_elf_preload_parse_symbols(ef);

	return (link_elf_link_common_finish(lf));
}