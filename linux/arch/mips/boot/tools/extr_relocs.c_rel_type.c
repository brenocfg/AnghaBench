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
 unsigned int ARRAY_SIZE (char const* const*) ; 
 char const* const REL_TYPE (int /*<<< orphan*/ ) ; 
#define  R_MIPS_16 145 
#define  R_MIPS_26 144 
#define  R_MIPS_32 143 
#define  R_MIPS_64 142 
#define  R_MIPS_CALL16 141 
#define  R_MIPS_GOT16 140 
#define  R_MIPS_GPREL16 139 
#define  R_MIPS_GPREL32 138 
#define  R_MIPS_HI16 137 
#define  R_MIPS_HIGHER 136 
#define  R_MIPS_HIGHEST 135 
#define  R_MIPS_LITERAL 134 
#define  R_MIPS_LO16 133 
#define  R_MIPS_NONE 132 
#define  R_MIPS_PC16 131 
#define  R_MIPS_PC21_S2 130 
#define  R_MIPS_PC26_S2 129 
#define  R_MIPS_REL32 128 

__attribute__((used)) static const char *rel_type(unsigned type)
{
	static const char * const type_name[] = {
#define REL_TYPE(X)[X] = #X
		REL_TYPE(R_MIPS_NONE),
		REL_TYPE(R_MIPS_16),
		REL_TYPE(R_MIPS_32),
		REL_TYPE(R_MIPS_REL32),
		REL_TYPE(R_MIPS_26),
		REL_TYPE(R_MIPS_HI16),
		REL_TYPE(R_MIPS_LO16),
		REL_TYPE(R_MIPS_GPREL16),
		REL_TYPE(R_MIPS_LITERAL),
		REL_TYPE(R_MIPS_GOT16),
		REL_TYPE(R_MIPS_PC16),
		REL_TYPE(R_MIPS_CALL16),
		REL_TYPE(R_MIPS_GPREL32),
		REL_TYPE(R_MIPS_64),
		REL_TYPE(R_MIPS_HIGHER),
		REL_TYPE(R_MIPS_HIGHEST),
		REL_TYPE(R_MIPS_PC21_S2),
		REL_TYPE(R_MIPS_PC26_S2),
#undef REL_TYPE
	};
	const char *name = "unknown type rel type name";

	if (type < ARRAY_SIZE(type_name) && type_name[type])
		name = type_name[type];
	return name;
}