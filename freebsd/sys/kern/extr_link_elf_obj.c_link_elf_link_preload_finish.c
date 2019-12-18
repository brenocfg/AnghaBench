#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* linker_file_t ;
typedef  scalar_t__ elf_file_t ;
struct TYPE_5__ {int /*<<< orphan*/  ctors_size; int /*<<< orphan*/  ctors_addr; } ;

/* Variables and functions */
 int elf_cpu_load_file (TYPE_1__*) ; 
 int /*<<< orphan*/  link_elf_invoke_ctors (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_elf_protect (scalar_t__) ; 
 int link_elf_reloc_local (TYPE_1__*,int) ; 
 int relocate_file (scalar_t__) ; 

__attribute__((used)) static int
link_elf_link_preload_finish(linker_file_t lf)
{
	elf_file_t ef;
	int error;

	ef = (elf_file_t)lf;
	error = relocate_file(ef);
	if (error)
		return (error);

	/* Notify MD code that a module is being loaded. */
	error = elf_cpu_load_file(lf);
	if (error)
		return (error);

#if defined(__i386__) || defined(__amd64__)
	/* Now ifuncs. */
	error = link_elf_reloc_local(lf, true);
	if (error != 0)
		return (error);
#endif

	/* Apply protections now that relocation processing is complete. */
	link_elf_protect(ef);

	link_elf_invoke_ctors(lf->ctors_addr, lf->ctors_size);
	return (0);
}