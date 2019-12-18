#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  linker_file_t ;
typedef  int (* elf_lookup_fn ) (int /*<<< orphan*/ ,int,int,scalar_t__*) ;
struct TYPE_4__ {scalar_t__ r_offset; int /*<<< orphan*/  r_info; } ;
struct TYPE_3__ {scalar_t__ r_offset; scalar_t__ r_addend; int /*<<< orphan*/  r_info; } ;
typedef  int Elf_Word ;
typedef  TYPE_1__ Elf_Rela ;
typedef  TYPE_2__ Elf_Rel ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */
#define  ELF_RELOC_REL 134 
#define  ELF_RELOC_RELA 133 
 int ELF_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF_R_TYPE (int /*<<< orphan*/ ) ; 
#define  R_ARM_ABS32 132 
#define  R_ARM_COPY 131 
#define  R_ARM_JUMP_SLOT 130 
#define  R_ARM_NONE 129 
#define  R_ARM_RELATIVE 128 
 scalar_t__ elf_relocaddr (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ load_ptr (scalar_t__*) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  store_ptr (scalar_t__*,scalar_t__) ; 

__attribute__((used)) static int
elf_reloc_internal(linker_file_t lf, Elf_Addr relocbase, const void *data,
    int type, int local, elf_lookup_fn lookup)
{
	Elf_Addr *where;
	Elf_Addr addr;
	Elf_Addr addend;
	Elf_Word rtype, symidx;
	const Elf_Rel *rel;
	const Elf_Rela *rela;
	int error;

	switch (type) {
	case ELF_RELOC_REL:
		rel = (const Elf_Rel *)data;
		where = (Elf_Addr *) (relocbase + rel->r_offset);
		addend = load_ptr(where);
		rtype = ELF_R_TYPE(rel->r_info);
		symidx = ELF_R_SYM(rel->r_info);
		break;
	case ELF_RELOC_RELA:
		rela = (const Elf_Rela *)data;
		where = (Elf_Addr *) (relocbase + rela->r_offset);
		addend = rela->r_addend;
		rtype = ELF_R_TYPE(rela->r_info);
		symidx = ELF_R_SYM(rela->r_info);
		break;
	default:
		panic("unknown reloc type %d\n", type);
	}

	if (local) {
		if (rtype == R_ARM_RELATIVE) {	/* A + B */
			addr = elf_relocaddr(lf, relocbase + addend);
			if (load_ptr(where) != addr)
				store_ptr(where, addr);
		}
		return (0);
	}

	switch (rtype) {

		case R_ARM_NONE:	/* none */
			break;

		case R_ARM_ABS32:
			error = lookup(lf, symidx, 1, &addr);
			if (error != 0)
				return -1;
			store_ptr(where, addr + load_ptr(where));
			break;

		case R_ARM_COPY:	/* none */
			/*
			 * There shouldn't be copy relocations in kernel
			 * objects.
			 */
			printf("kldload: unexpected R_COPY relocation\n");
			return -1;
			break;

		case R_ARM_JUMP_SLOT:
			error = lookup(lf, symidx, 1, &addr);
			if (error == 0) {
				store_ptr(where, addr);
				return (0);
			}
			return (-1);
		case R_ARM_RELATIVE:
			break;

		default:
			printf("kldload: unexpected relocation type %d\n",
			       rtype);
			return -1;
	}
	return(0);
}