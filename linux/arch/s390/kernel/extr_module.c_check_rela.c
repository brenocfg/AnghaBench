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
struct TYPE_4__ {unsigned long got_size; unsigned long plt_size; struct mod_arch_syminfo* syminfo; } ;
struct module {TYPE_1__ arch; } ;
struct mod_arch_syminfo {unsigned long got_offset; unsigned long plt_offset; } ;
struct TYPE_5__ {int /*<<< orphan*/  r_info; } ;
typedef  TYPE_2__ Elf_Rela ;

/* Variables and functions */
 int ELF_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF_R_TYPE (int /*<<< orphan*/ ) ; 
 unsigned long PLT_ENTRY_SIZE ; 
#define  R_390_COPY 150 
#define  R_390_GLOB_DAT 149 
#define  R_390_GOT12 148 
#define  R_390_GOT16 147 
#define  R_390_GOT20 146 
#define  R_390_GOT32 145 
#define  R_390_GOT64 144 
#define  R_390_GOTENT 143 
#define  R_390_GOTPLT12 142 
#define  R_390_GOTPLT16 141 
#define  R_390_GOTPLT20 140 
#define  R_390_GOTPLT32 139 
#define  R_390_GOTPLT64 138 
#define  R_390_GOTPLTENT 137 
#define  R_390_JMP_SLOT 136 
#define  R_390_PLT16DBL 135 
#define  R_390_PLT32 134 
#define  R_390_PLT32DBL 133 
#define  R_390_PLT64 132 
#define  R_390_PLTOFF16 131 
#define  R_390_PLTOFF32 130 
#define  R_390_PLTOFF64 129 
#define  R_390_RELATIVE 128 

__attribute__((used)) static void check_rela(Elf_Rela *rela, struct module *me)
{
	struct mod_arch_syminfo *info;

	info = me->arch.syminfo + ELF_R_SYM (rela->r_info);
	switch (ELF_R_TYPE (rela->r_info)) {
	case R_390_GOT12:	/* 12 bit GOT offset.  */
	case R_390_GOT16:	/* 16 bit GOT offset.  */
	case R_390_GOT20:	/* 20 bit GOT offset.  */
	case R_390_GOT32:	/* 32 bit GOT offset.  */
	case R_390_GOT64:	/* 64 bit GOT offset.  */
	case R_390_GOTENT:	/* 32 bit PC rel. to GOT entry shifted by 1. */
	case R_390_GOTPLT12:	/* 12 bit offset to jump slot.	*/
	case R_390_GOTPLT16:	/* 16 bit offset to jump slot.  */
	case R_390_GOTPLT20:	/* 20 bit offset to jump slot.  */
	case R_390_GOTPLT32:	/* 32 bit offset to jump slot.  */
	case R_390_GOTPLT64:	/* 64 bit offset to jump slot.	*/
	case R_390_GOTPLTENT:	/* 32 bit rel. offset to jump slot >> 1. */
		if (info->got_offset == -1UL) {
			info->got_offset = me->arch.got_size;
			me->arch.got_size += sizeof(void*);
		}
		break;
	case R_390_PLT16DBL:	/* 16 bit PC rel. PLT shifted by 1.  */
	case R_390_PLT32DBL:	/* 32 bit PC rel. PLT shifted by 1.  */
	case R_390_PLT32:	/* 32 bit PC relative PLT address.  */
	case R_390_PLT64:	/* 64 bit PC relative PLT address.  */
	case R_390_PLTOFF16:	/* 16 bit offset from GOT to PLT. */
	case R_390_PLTOFF32:	/* 32 bit offset from GOT to PLT. */
	case R_390_PLTOFF64:	/* 16 bit offset from GOT to PLT. */
		if (info->plt_offset == -1UL) {
			info->plt_offset = me->arch.plt_size;
			me->arch.plt_size += PLT_ENTRY_SIZE;
		}
		break;
	case R_390_COPY:
	case R_390_GLOB_DAT:
	case R_390_JMP_SLOT:
	case R_390_RELATIVE:
		/* Only needed if we want to support loading of 
		   modules linked with -shared. */
		break;
	}
}