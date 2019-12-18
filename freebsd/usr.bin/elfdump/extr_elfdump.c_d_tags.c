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
typedef  int /*<<< orphan*/  unknown_tag ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ u_int64_t ;

/* Variables and functions */
#define  DT_ADDRRNGLO 185 
#define  DT_AUDIT 184 
#define  DT_AUXILIARY 183 
#define  DT_BIND_NOW 182 
#define  DT_CONFIG 181 
#define  DT_DEBUG 180 
#define  DT_DEPAUDIT 179 
#define  DT_FEATURE 178 
#define  DT_FILTER 177 
#define  DT_FINI 176 
#define  DT_FINI_ARRAY 175 
#define  DT_FINI_ARRAYSZ 174 
#define  DT_FLAGS 173 
#define  DT_FLAGS_1 172 
#define  DT_GNU_HASH 171 
#define  DT_HASH 170 
#define  DT_INIT 169 
#define  DT_INIT_ARRAY 168 
#define  DT_INIT_ARRAYSZ 167 
#define  DT_JMPREL 166 
#define  DT_MOVEENT 165 
#define  DT_MOVESZ 164 
#define  DT_MOVETAB 163 
#define  DT_NEEDED 162 
#define  DT_NULL 161 
#define  DT_PLTGOT 160 
#define  DT_PLTPAD 159 
#define  DT_PLTPADSZ 158 
#define  DT_PLTREL 157 
#define  DT_PLTRELSZ 156 
#define  DT_POSFLAG_1 155 
#define  DT_PREINIT_ARRAY 154 
#define  DT_PREINIT_ARRAYSZ 153 
#define  DT_REL 152 
#define  DT_RELA 151 
#define  DT_RELACOUNT 150 
#define  DT_RELAENT 149 
#define  DT_RELASZ 148 
#define  DT_RELCOUNT 147 
#define  DT_RELENT 146 
#define  DT_RELSZ 145 
#define  DT_RPATH 144 
#define  DT_RUNPATH 143 
#define  DT_SONAME 142 
#define  DT_STRSZ 141 
#define  DT_STRTAB 140 
#define  DT_SYMBOLIC 139 
#define  DT_SYMENT 138 
#define  DT_SYMINENT 137 
#define  DT_SYMINFO 136 
#define  DT_SYMINSZ 135 
#define  DT_SYMTAB 134 
#define  DT_TEXTREL 133 
#define  DT_USED 132 
#define  DT_VERDEF 131 
#define  DT_VERDEFNUM 130 
#define  DT_VERNEED 129 
#define  DT_VERNEEDNUM 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
d_tags(u_int64_t tag)
{
	static char unknown_tag[48];

	switch (tag) {
	case DT_NULL:		return "DT_NULL";
	case DT_NEEDED:		return "DT_NEEDED";
	case DT_PLTRELSZ:	return "DT_PLTRELSZ";
	case DT_PLTGOT:		return "DT_PLTGOT";
	case DT_HASH:		return "DT_HASH";
	case DT_STRTAB:		return "DT_STRTAB";
	case DT_SYMTAB:		return "DT_SYMTAB";
	case DT_RELA:		return "DT_RELA";
	case DT_RELASZ:		return "DT_RELASZ";
	case DT_RELAENT:	return "DT_RELAENT";
	case DT_STRSZ:		return "DT_STRSZ";
	case DT_SYMENT:		return "DT_SYMENT";
	case DT_INIT:		return "DT_INIT";
	case DT_FINI:		return "DT_FINI";
	case DT_SONAME:		return "DT_SONAME";
	case DT_RPATH:		return "DT_RPATH";
	case DT_SYMBOLIC:	return "DT_SYMBOLIC";
	case DT_REL:		return "DT_REL";
	case DT_RELSZ:		return "DT_RELSZ";
	case DT_RELENT:		return "DT_RELENT";
	case DT_PLTREL:		return "DT_PLTREL";
	case DT_DEBUG:		return "DT_DEBUG";
	case DT_TEXTREL:	return "DT_TEXTREL";
	case DT_JMPREL:		return "DT_JMPREL";
	case DT_BIND_NOW:	return "DT_BIND_NOW";
	case DT_INIT_ARRAY:	return "DT_INIT_ARRAY";
	case DT_FINI_ARRAY:	return "DT_FINI_ARRAY";
	case DT_INIT_ARRAYSZ:	return "DT_INIT_ARRAYSZ";
	case DT_FINI_ARRAYSZ:	return "DT_FINI_ARRAYSZ";
	case DT_RUNPATH:	return "DT_RUNPATH";
	case DT_FLAGS:		return "DT_FLAGS";
	case DT_PREINIT_ARRAY:	return "DT_PREINIT_ARRAY"; /* XXX DT_ENCODING */
	case DT_PREINIT_ARRAYSZ:return "DT_PREINIT_ARRAYSZ";
	/* 0x6000000D - 0x6ffff000 operating system-specific semantics */
	case 0x6ffffdf5:	return "DT_GNU_PRELINKED";
	case 0x6ffffdf6:	return "DT_GNU_CONFLICTSZ";
	case 0x6ffffdf7:	return "DT_GNU_LIBLISTSZ";
	case 0x6ffffdf8:	return "DT_SUNW_CHECKSUM";
	case DT_PLTPADSZ:	return "DT_PLTPADSZ";
	case DT_MOVEENT:	return "DT_MOVEENT";
	case DT_MOVESZ:		return "DT_MOVESZ";
	case DT_FEATURE:	return "DT_FEATURE";
	case DT_POSFLAG_1:	return "DT_POSFLAG_1";
	case DT_SYMINSZ:	return "DT_SYMINSZ";
	case DT_SYMINENT :	return "DT_SYMINENT (DT_VALRNGHI)";
	case DT_ADDRRNGLO:	return "DT_ADDRRNGLO";
	case DT_GNU_HASH:	return "DT_GNU_HASH";
	case 0x6ffffef8:	return "DT_GNU_CONFLICT";
	case 0x6ffffef9:	return "DT_GNU_LIBLIST";
	case DT_CONFIG:		return "DT_CONFIG";
	case DT_DEPAUDIT:	return "DT_DEPAUDIT";
	case DT_AUDIT:		return "DT_AUDIT";
	case DT_PLTPAD:		return "DT_PLTPAD";
	case DT_MOVETAB:	return "DT_MOVETAB";
	case DT_SYMINFO :	return "DT_SYMINFO (DT_ADDRRNGHI)";
	case DT_RELACOUNT:	return "DT_RELACOUNT";
	case DT_RELCOUNT:	return "DT_RELCOUNT";
	case DT_FLAGS_1:	return "DT_FLAGS_1";
	case DT_VERDEF:		return "DT_VERDEF";
	case DT_VERDEFNUM:	return "DT_VERDEFNUM";
	case DT_VERNEED:	return "DT_VERNEED";
	case DT_VERNEEDNUM:	return "DT_VERNEEDNUM";
	case 0x6ffffff0:	return "DT_GNU_VERSYM";
	/* 0x70000000 - 0x7fffffff processor-specific semantics */
	case 0x70000000:	return "DT_IA_64_PLT_RESERVE";
	case DT_AUXILIARY:	return "DT_AUXILIARY";
	case DT_USED:		return "DT_USED";
	case DT_FILTER:		return "DT_FILTER";
	}
	snprintf(unknown_tag, sizeof(unknown_tag),
		"ERROR: TAG NOT DEFINED -- tag 0x%jx", (uintmax_t)tag);
	return (unknown_tag);
}