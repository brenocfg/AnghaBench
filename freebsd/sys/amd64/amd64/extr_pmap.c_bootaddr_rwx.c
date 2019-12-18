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
typedef  scalar_t__ vm_paddr_t ;
typedef  int pt_entry_t ;

/* Variables and functions */
 scalar_t__ KERNBASE ; 
 int X86_PG_RW ; 
 scalar_t__ _end ; 
 scalar_t__ brwsection ; 
 scalar_t__ btext ; 
 scalar_t__ etext ; 
 int pg_nx ; 
 scalar_t__ round_2mpage (scalar_t__) ; 
 scalar_t__ trunc_2mpage (scalar_t__) ; 

__attribute__((used)) static inline pt_entry_t
bootaddr_rwx(vm_paddr_t pa)
{

	/*
	 * The kernel is loaded at a 2MB-aligned address, and memory below that
	 * need not be executable.  The .bss section is padded to a 2MB
	 * boundary, so memory following the kernel need not be executable
	 * either.  Preloaded kernel modules have their mapping permissions
	 * fixed up by the linker.
	 */
	if (pa < trunc_2mpage(btext - KERNBASE) ||
	    pa >= trunc_2mpage(_end - KERNBASE))
		return (X86_PG_RW | pg_nx);

	/*
	 * The linker should ensure that the read-only and read-write
	 * portions don't share the same 2M page, so this shouldn't
	 * impact read-only data. However, in any case, any page with
	 * read-write data needs to be read-write.
	 */
	if (pa >= trunc_2mpage(brwsection - KERNBASE))
		return (X86_PG_RW | pg_nx);

	/*
	 * Mark any 2M page containing kernel text as read-only. Mark
	 * other pages with read-only data as read-only and not executable.
	 * (It is likely a small portion of the read-only data section will
	 * be marked as read-only, but executable. This should be acceptable
	 * since the read-only protection will keep the data from changing.)
	 * Note that fixups to the .text section will still work until we
	 * set CR0.WP.
	 */
	if (pa < round_2mpage(etext - KERNBASE))
		return (0);
	return (pg_nx);
}