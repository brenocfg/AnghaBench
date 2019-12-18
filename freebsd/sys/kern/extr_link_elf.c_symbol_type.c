#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* elf_file_t ;
struct TYPE_5__ {int /*<<< orphan*/  st_info; } ;
struct TYPE_4__ {TYPE_2__* symtab; } ;
typedef  TYPE_2__ Elf_Sym ;
typedef  int /*<<< orphan*/  Elf_Size ;

/* Variables and functions */
 int ELF_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 int STT_NOTYPE ; 

__attribute__((used)) static int
symbol_type(elf_file_t ef, Elf_Size r_info)
{
	const Elf_Sym *ref;

	if (ELF_R_SYM(r_info)) {
		ref = ef->symtab + ELF_R_SYM(r_info);
		return (ELF_ST_TYPE(ref->st_info));
	}
	return (STT_NOTYPE);
}