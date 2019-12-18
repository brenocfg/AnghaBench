#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* e_ident; int /*<<< orphan*/  e_machine; int /*<<< orphan*/  e_type; } ;
typedef  TYPE_1__ Elf32_Ehdr ;

/* Variables and functions */
 size_t EI_CLASS ; 
 size_t EI_DATA ; 
 size_t EI_OSABI ; 
 size_t EI_VERSION ; 
 scalar_t__ ELFCLASS32 ; 
 scalar_t__ ELFDATA2MSB ; 
 scalar_t__ ELFOSABI_STANDALONE ; 
 scalar_t__ EM_PPC ; 
 scalar_t__ ET_CORE ; 
 scalar_t__ EV_CURRENT ; 
 int /*<<< orphan*/  IS_ELF (TYPE_1__) ; 
 scalar_t__ be16toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
valid_elf_header(Elf32_Ehdr *eh)
{

	if (!IS_ELF(*eh))
		return (0);
	if (eh->e_ident[EI_CLASS] != ELFCLASS32)
		return (0);
	if (eh->e_ident[EI_DATA] != ELFDATA2MSB)
		return (0);
	if (eh->e_ident[EI_VERSION] != EV_CURRENT)
		return (0);
	if (eh->e_ident[EI_OSABI] != ELFOSABI_STANDALONE)
		return (0);
	if (be16toh(eh->e_type) != ET_CORE)
		return (0);
	if (be16toh(eh->e_machine) != EM_PPC)
		return (0);
	/* Can't think of anything else to check... */
	return (1);
}