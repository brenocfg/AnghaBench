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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ u_int64_t ;
typedef  size_t elf_member_t ;
struct TYPE_3__ {int* e_ident; } ;
typedef  TYPE_1__ Elf32_Ehdr ;

/* Variables and functions */
 size_t EI_CLASS ; 
#define  ELFCLASS32 130 
#define  ELFCLASS64 129 
#define  ELFCLASSNONE 128 
 size_t* elf32_offsets ; 
 size_t* elf64_offsets ; 
 int /*<<< orphan*/  errx (int,char*) ; 

__attribute__((used)) static u_int64_t
elf_get_byte(Elf32_Ehdr *e, void *base, elf_member_t member)
{
	u_int64_t val;

	val = 0;
	switch (e->e_ident[EI_CLASS]) {
	case ELFCLASS32:
		val = ((uint8_t *)base)[elf32_offsets[member]];
		break;
	case ELFCLASS64:
		val = ((uint8_t *)base)[elf64_offsets[member]];
		break;
	case ELFCLASSNONE:
		errx(1, "invalid class");
	}

	return val;
}