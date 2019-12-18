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
typedef  int /*<<< orphan*/  unknown_buf ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint64_t ;

/* Variables and functions */
#define  EM_ARM 160 
#define  EM_IA_64 159 
#define  EM_MIPS 158 
#define  SHT_ARM_ATTRIBUTES 157 
#define  SHT_ARM_DEBUGOVERLAY 156 
#define  SHT_ARM_EXIDX 155 
#define  SHT_ARM_OVERLAYSECTION 154 
#define  SHT_ARM_PREEMPTMAP 153 
#define  SHT_DYNAMIC 152 
#define  SHT_DYNSYM 151 
#define  SHT_FINI_ARRAY 150 
#define  SHT_GNU_HASH 149 
#define  SHT_GROUP 148 
#define  SHT_HASH 147 
#define  SHT_INIT_ARRAY 146 
#define  SHT_MIPS_ABIFLAGS 145 
#define  SHT_MIPS_OPTIONS 144 
#define  SHT_MIPS_REGINFO 143 
#define  SHT_NOBITS 142 
#define  SHT_NOTE 141 
#define  SHT_NULL 140 
#define  SHT_PREINIT_ARRAY 139 
#define  SHT_PROGBITS 138 
#define  SHT_REL 137 
#define  SHT_RELA 136 
#define  SHT_SHLIB 135 
#define  SHT_STRTAB 134 
#define  SHT_SUNW_dof 133 
#define  SHT_SUNW_verdef 132 
#define  SHT_SUNW_verneed 131 
#define  SHT_SUNW_versym 130 
#define  SHT_SYMTAB 129 
#define  SHT_SYMTAB_SHNDX 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
sh_types(uint64_t machine, uint64_t sht) {
	static char unknown_buf[64];

	if (sht < 0x60000000) {
		switch (sht) {
		case SHT_NULL:		return "SHT_NULL";
		case SHT_PROGBITS:	return "SHT_PROGBITS";
		case SHT_SYMTAB:	return "SHT_SYMTAB";
		case SHT_STRTAB:	return "SHT_STRTAB";
		case SHT_RELA:		return "SHT_RELA";
		case SHT_HASH:		return "SHT_HASH";
		case SHT_DYNAMIC:	return "SHT_DYNAMIC";
		case SHT_NOTE:		return "SHT_NOTE";
		case SHT_NOBITS:	return "SHT_NOBITS";
		case SHT_REL:		return "SHT_REL";
		case SHT_SHLIB:		return "SHT_SHLIB";
		case SHT_DYNSYM:	return "SHT_DYNSYM";
		case SHT_INIT_ARRAY:	return "SHT_INIT_ARRAY";
		case SHT_FINI_ARRAY:	return "SHT_FINI_ARRAY";
		case SHT_PREINIT_ARRAY:	return "SHT_PREINIT_ARRAY";
		case SHT_GROUP:		return "SHT_GROUP";
		case SHT_SYMTAB_SHNDX:	return "SHT_SYMTAB_SHNDX";
		}
		snprintf(unknown_buf, sizeof(unknown_buf),
		    "ERROR: SHT %ju NOT DEFINED", (uintmax_t)sht);
		return (unknown_buf);
	} else if (sht < 0x70000000) {
		/* 0x60000000-0x6fffffff operating system-specific semantics */
		switch (sht) {
		case 0x6ffffff0:	return "XXX:VERSYM";
		case SHT_SUNW_dof:	return "SHT_SUNW_dof";
		case SHT_GNU_HASH:	return "SHT_GNU_HASH";
		case 0x6ffffff7:	return "SHT_GNU_LIBLIST";
		case 0x6ffffffc:	return "XXX:VERDEF";
		case SHT_SUNW_verdef:	return "SHT_SUNW(GNU)_verdef";
		case SHT_SUNW_verneed:	return "SHT_SUNW(GNU)_verneed";
		case SHT_SUNW_versym:	return "SHT_SUNW(GNU)_versym";
		}
		snprintf(unknown_buf, sizeof(unknown_buf),
		    "ERROR: OS-SPECIFIC SHT 0x%jx NOT DEFINED",
		     (uintmax_t)sht);
		return (unknown_buf);
	} else if (sht < 0x80000000) {
		/* 0x70000000-0x7fffffff processor-specific semantics */
		switch (machine) {
		case EM_ARM:
			switch (sht) {
			case SHT_ARM_EXIDX: return "SHT_ARM_EXIDX";
			case SHT_ARM_PREEMPTMAP:return "SHT_ARM_PREEMPTMAP";
			case SHT_ARM_ATTRIBUTES:return "SHT_ARM_ATTRIBUTES";
			case SHT_ARM_DEBUGOVERLAY:
			    return "SHT_ARM_DEBUGOVERLAY";
			case SHT_ARM_OVERLAYSECTION:
			    return "SHT_ARM_OVERLAYSECTION";
			}
			break;
		case EM_IA_64:
			switch (sht) {
			case 0x70000000: return "SHT_IA_64_EXT";
			case 0x70000001: return "SHT_IA_64_UNWIND";
			}
			break;
		case EM_MIPS:
			switch (sht) {
			case SHT_MIPS_REGINFO: return "SHT_MIPS_REGINFO";
			case SHT_MIPS_OPTIONS: return "SHT_MIPS_OPTIONS";
			case SHT_MIPS_ABIFLAGS: return "SHT_MIPS_ABIFLAGS";
			}
			break;
		}
		switch (sht) {
		case 0x7ffffffd: return "XXX:AUXILIARY";
		case 0x7fffffff: return "XXX:FILTER";
		}
		snprintf(unknown_buf, sizeof(unknown_buf),
		    "ERROR: PROCESSOR-SPECIFIC SHT 0x%jx NOT DEFINED",
		     (uintmax_t)sht);
		return (unknown_buf);
	} else {
		/* 0x80000000-0xffffffff application programs */
		snprintf(unknown_buf, sizeof(unknown_buf),
		    "ERROR: SHT 0x%jx NOT DEFINED",
		     (uintmax_t)sht);
		return (unknown_buf);
	}
}