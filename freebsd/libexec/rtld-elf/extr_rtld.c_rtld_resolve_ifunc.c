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
typedef  int /*<<< orphan*/  Elf_Sym ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */
 scalar_t__ call_ifunc_resolver (void*) ; 
 scalar_t__ make_function_pointer (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

void *
rtld_resolve_ifunc(const Obj_Entry *obj, const Elf_Sym *def)
{
	void *ptr;
	Elf_Addr target;

	ptr = (void *)make_function_pointer(def, obj);
	target = call_ifunc_resolver(ptr);
	return ((void *)target);
}