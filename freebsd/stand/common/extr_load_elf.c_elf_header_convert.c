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
typedef  int /*<<< orphan*/  Elf_Ehdr ;

/* Variables and functions */
 int /*<<< orphan*/  CONVERT_SWITCH (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEADER_FIELDS ; 

__attribute__((used)) static int elf_header_convert(Elf_Ehdr *ehdr)
{
	/*
	 * Fixup ELF header endianness.
	 *
	 * The Xhdr structure was loaded using block read call to optimize file
	 * accesses. It might happen, that the endianness of the system memory
	 * is different that endianness of the ELF header.  Swap fields here to
	 * guarantee that Xhdr always contain valid data regardless of
	 * architecture.
	 */
#define HEADER_FIELDS(b, e)			\
	CONVERT_FIELD(b, e_type, e);		\
	CONVERT_FIELD(b, e_machine, e);		\
	CONVERT_FIELD(b, e_version, e);		\
	CONVERT_FIELD(b, e_entry, e);		\
	CONVERT_FIELD(b, e_phoff, e);		\
	CONVERT_FIELD(b, e_shoff, e);		\
	CONVERT_FIELD(b, e_flags, e);		\
	CONVERT_FIELD(b, e_ehsize, e);		\
	CONVERT_FIELD(b, e_phentsize, e);	\
	CONVERT_FIELD(b, e_phnum, e);		\
	CONVERT_FIELD(b, e_shentsize, e);	\
	CONVERT_FIELD(b, e_shnum, e);		\
	CONVERT_FIELD(b, e_shstrndx, e)

	CONVERT_SWITCH(ehdr, ehdr, HEADER_FIELDS);

#undef HEADER_FIELDS

	return (0);
}