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
struct elfhdr {int e_phoff; int e_ehsize; int e_phentsize; scalar_t__ e_shstrndx; scalar_t__ e_shnum; scalar_t__ e_shentsize; scalar_t__ e_phnum; scalar_t__ e_flags; scalar_t__ e_shoff; scalar_t__ e_entry; void* e_version; int /*<<< orphan*/  e_machine; int /*<<< orphan*/  e_type; void** e_ident; } ;
struct elf_phdr {int dummy; } ;

/* Variables and functions */
 size_t EI_CLASS ; 
 size_t EI_DATA ; 
 int EI_NIDENT ; 
 size_t EI_OSABI ; 
 int EI_PAD ; 
 size_t EI_VERSION ; 
 int /*<<< orphan*/  ELFMAG ; 
 int /*<<< orphan*/  ELF_ARCH ; 
 void* ELF_CLASS ; 
 void* ELF_DATA ; 
 void* ELF_OSABI ; 
 int /*<<< orphan*/  ET_CORE ; 
 void* EV_CURRENT ; 
 int /*<<< orphan*/  SELFMAG ; 
 scalar_t__ _CALL_ELF ; 
 int /*<<< orphan*/  memcpy (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fadump_init_elfcore_header(char *bufp)
{
	struct elfhdr *elf;

	elf = (struct elfhdr *) bufp;
	bufp += sizeof(struct elfhdr);
	memcpy(elf->e_ident, ELFMAG, SELFMAG);
	elf->e_ident[EI_CLASS] = ELF_CLASS;
	elf->e_ident[EI_DATA] = ELF_DATA;
	elf->e_ident[EI_VERSION] = EV_CURRENT;
	elf->e_ident[EI_OSABI] = ELF_OSABI;
	memset(elf->e_ident+EI_PAD, 0, EI_NIDENT-EI_PAD);
	elf->e_type = ET_CORE;
	elf->e_machine = ELF_ARCH;
	elf->e_version = EV_CURRENT;
	elf->e_entry = 0;
	elf->e_phoff = sizeof(struct elfhdr);
	elf->e_shoff = 0;
#if defined(_CALL_ELF)
	elf->e_flags = _CALL_ELF;
#else
	elf->e_flags = 0;
#endif
	elf->e_ehsize = sizeof(struct elfhdr);
	elf->e_phentsize = sizeof(struct elf_phdr);
	elf->e_phnum = 0;
	elf->e_shentsize = 0;
	elf->e_shnum = 0;
	elf->e_shstrndx = 0;

	return 0;
}