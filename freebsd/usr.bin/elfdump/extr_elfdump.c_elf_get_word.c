#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int64_t ;
typedef  size_t elf_member_t ;
struct TYPE_3__ {int* e_ident; } ;
typedef  TYPE_1__ Elf32_Ehdr ;

/* Variables and functions */
 size_t EI_CLASS ; 
 size_t EI_DATA ; 
#define  ELFCLASS32 133 
#define  ELFCLASS64 132 
#define  ELFCLASSNONE 131 
#define  ELFDATA2LSB 130 
#define  ELFDATA2MSB 129 
#define  ELFDATANONE 128 
 scalar_t__ be32dec (void*) ; 
 int /*<<< orphan*/ * elf32_offsets ; 
 int /*<<< orphan*/ * elf64_offsets ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ le32dec (void*) ; 

__attribute__((used)) static u_int64_t
elf_get_word(Elf32_Ehdr *e, void *base, elf_member_t member)
{
	u_int64_t val;

	val = 0;
	switch (e->e_ident[EI_CLASS]) {
	case ELFCLASS32:
		base = (char *)base + elf32_offsets[member];
		switch (e->e_ident[EI_DATA]) {
		case ELFDATA2MSB:
			val = be32dec(base);
			break;
		case ELFDATA2LSB:
			val = le32dec(base);
			break;
		case ELFDATANONE:
			errx(1, "invalid data format");
		}
		break;
	case ELFCLASS64:
		base = (char *)base + elf64_offsets[member];
		switch (e->e_ident[EI_DATA]) {
		case ELFDATA2MSB:
			val = be32dec(base);
			break;
		case ELFDATA2LSB:
			val = le32dec(base);
			break;
		case ELFDATANONE:
			errx(1, "invalid data format");
		}
		break;
	case ELFCLASSNONE:
		errx(1, "invalid class");
	}

	return val;
}