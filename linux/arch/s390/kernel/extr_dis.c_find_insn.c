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
struct s390_opcode_offset {unsigned char opcode; int byte; unsigned char mask; size_t offset; int count; } ;
struct s390_insn {unsigned char opfrag; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct s390_opcode_offset*) ; 
 struct s390_insn* opcode ; 
 struct s390_opcode_offset* opcode_offset ; 

struct s390_insn *find_insn(unsigned char *code)
{
	struct s390_opcode_offset *entry;
	struct s390_insn *insn;
	unsigned char opfrag;
	int i;

	/* Search the opcode offset table to find an entry which
	 * matches the beginning of the opcode. If there is no match
	 * the last entry will be used, which is the default entry for
	 * unknown instructions as well as 1-byte opcode instructions.
	 */
	for (i = 0; i < ARRAY_SIZE(opcode_offset); i++) {
		entry = &opcode_offset[i];
		if (entry->opcode == code[0])
			break;
	}

	opfrag = *(code + entry->byte) & entry->mask;

	insn = &opcode[entry->offset];
	for (i = 0; i < entry->count; i++) {
		if (insn->opfrag == opfrag)
			return insn;
		insn++;
	}
	return NULL;
}