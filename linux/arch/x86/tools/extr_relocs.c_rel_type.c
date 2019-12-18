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

/* Variables and functions */
 unsigned int ARRAY_SIZE (char const**) ; 
 char const* REL_TYPE (int /*<<< orphan*/ ) ; 
#define  R_386_16 159 
#define  R_386_32 158 
#define  R_386_8 157 
#define  R_386_COPY 156 
#define  R_386_GLOB_DAT 155 
#define  R_386_GOT32 154 
#define  R_386_GOTOFF 153 
#define  R_386_GOTPC 152 
#define  R_386_JMP_SLOT 151 
#define  R_386_NONE 150 
#define  R_386_PC16 149 
#define  R_386_PC32 148 
#define  R_386_PC8 147 
#define  R_386_PLT32 146 
#define  R_386_RELATIVE 145 
#define  R_X86_64_16 144 
#define  R_X86_64_32 143 
#define  R_X86_64_32S 142 
#define  R_X86_64_64 141 
#define  R_X86_64_8 140 
#define  R_X86_64_COPY 139 
#define  R_X86_64_GLOB_DAT 138 
#define  R_X86_64_GOT32 137 
#define  R_X86_64_GOTPCREL 136 
#define  R_X86_64_JUMP_SLOT 135 
#define  R_X86_64_NONE 134 
#define  R_X86_64_PC16 133 
#define  R_X86_64_PC32 132 
#define  R_X86_64_PC64 131 
#define  R_X86_64_PC8 130 
#define  R_X86_64_PLT32 129 
#define  R_X86_64_RELATIVE 128 

__attribute__((used)) static const char *rel_type(unsigned type)
{
	static const char *type_name[] = {
#define REL_TYPE(X) [X] = #X
#if ELF_BITS == 64
		REL_TYPE(R_X86_64_NONE),
		REL_TYPE(R_X86_64_64),
		REL_TYPE(R_X86_64_PC64),
		REL_TYPE(R_X86_64_PC32),
		REL_TYPE(R_X86_64_GOT32),
		REL_TYPE(R_X86_64_PLT32),
		REL_TYPE(R_X86_64_COPY),
		REL_TYPE(R_X86_64_GLOB_DAT),
		REL_TYPE(R_X86_64_JUMP_SLOT),
		REL_TYPE(R_X86_64_RELATIVE),
		REL_TYPE(R_X86_64_GOTPCREL),
		REL_TYPE(R_X86_64_32),
		REL_TYPE(R_X86_64_32S),
		REL_TYPE(R_X86_64_16),
		REL_TYPE(R_X86_64_PC16),
		REL_TYPE(R_X86_64_8),
		REL_TYPE(R_X86_64_PC8),
#else
		REL_TYPE(R_386_NONE),
		REL_TYPE(R_386_32),
		REL_TYPE(R_386_PC32),
		REL_TYPE(R_386_GOT32),
		REL_TYPE(R_386_PLT32),
		REL_TYPE(R_386_COPY),
		REL_TYPE(R_386_GLOB_DAT),
		REL_TYPE(R_386_JMP_SLOT),
		REL_TYPE(R_386_RELATIVE),
		REL_TYPE(R_386_GOTOFF),
		REL_TYPE(R_386_GOTPC),
		REL_TYPE(R_386_8),
		REL_TYPE(R_386_PC8),
		REL_TYPE(R_386_16),
		REL_TYPE(R_386_PC16),
#endif
#undef REL_TYPE
	};
	const char *name = "unknown type rel type name";
	if (type < ARRAY_SIZE(type_name) && type_name[type]) {
		name = type_name[type];
	}
	return name;
}