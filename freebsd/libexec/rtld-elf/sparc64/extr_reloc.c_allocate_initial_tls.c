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
typedef  int /*<<< orphan*/  Obj_Entry ;
typedef  int /*<<< orphan*/  Elf_Addr ;

/* Variables and functions */
 scalar_t__ RTLD_STATIC_TLS_EXTRA ; 
 int /*<<< orphan*/ * allocate_tls (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ tls_last_offset ; 
 scalar_t__ tls_static_space ; 

void
allocate_initial_tls(Obj_Entry *objs)
{
	Elf_Addr* tpval;

	/*
	 * Fix the size of the static TLS block by using the maximum offset
	 * allocated so far and adding a bit for dynamic modules to use.
	 */
	tls_static_space = tls_last_offset + RTLD_STATIC_TLS_EXTRA;
	tpval = allocate_tls(objs, NULL, 3 * sizeof(Elf_Addr),
	     sizeof(Elf_Addr));
	__asm __volatile("mov %0, %%g7" : : "r" (tpval));
}