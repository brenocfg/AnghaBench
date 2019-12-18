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
typedef  int /*<<< orphan*/  Elf_Phdr ;
typedef  int /*<<< orphan*/  Elf_Ehdr ;

/* Variables and functions */
 int /*<<< orphan*/  CONVERT_SWITCH (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROGRAM_HEADER_FIELDS ; 

__attribute__((used)) static int elf_program_header_convert(const Elf_Ehdr *ehdr, Elf_Phdr *phdr)
{
#define PROGRAM_HEADER_FIELDS(b, e)		\
	CONVERT_FIELD(b, p_type, e);		\
	CONVERT_FIELD(b, p_flags, e);		\
	CONVERT_FIELD(b, p_offset, e);		\
	CONVERT_FIELD(b, p_vaddr, e);		\
	CONVERT_FIELD(b, p_paddr, e);		\
	CONVERT_FIELD(b, p_filesz, e);		\
	CONVERT_FIELD(b, p_memsz, e);		\
	CONVERT_FIELD(b, p_align, e)

	CONVERT_SWITCH(ehdr, phdr, PROGRAM_HEADER_FIELDS);

#undef PROGRAM_HEADER_FIELDS

	return (0);
}