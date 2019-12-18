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
typedef  int /*<<< orphan*/  Elf_Shdr ;
typedef  int /*<<< orphan*/  Elf_Ehdr ;

/* Variables and functions */
 int /*<<< orphan*/  CONVERT_SWITCH (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SECTION_HEADER_FIELDS ; 

__attribute__((used)) static int elf_section_header_convert(const Elf_Ehdr *ehdr, Elf_Shdr *shdr)
{
#define SECTION_HEADER_FIELDS(b, e)		\
	CONVERT_FIELD(b, sh_name, e);		\
	CONVERT_FIELD(b, sh_type, e);		\
	CONVERT_FIELD(b, sh_link, e);		\
	CONVERT_FIELD(b, sh_info, e);		\
	CONVERT_FIELD(b, sh_flags, e);		\
	CONVERT_FIELD(b, sh_addr, e);		\
	CONVERT_FIELD(b, sh_offset, e);		\
	CONVERT_FIELD(b, sh_size, e);		\
	CONVERT_FIELD(b, sh_addralign, e);	\
	CONVERT_FIELD(b, sh_entsize, e)

	CONVERT_SWITCH(ehdr, shdr, SECTION_HEADER_FIELDS);

#undef SECTION_HEADER_FIELDS

	return (0);
}