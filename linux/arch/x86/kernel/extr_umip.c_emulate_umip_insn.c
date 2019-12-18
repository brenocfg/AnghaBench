#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u64 ;
typedef  unsigned long u16 ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;
struct insn {int opnd_bytes; TYPE_1__ modrm; } ;

/* Variables and functions */
 unsigned long CR0_STATE ; 
 int EINVAL ; 
 unsigned long UMIP_DUMMY_GDT_BASE ; 
 unsigned long UMIP_DUMMY_IDT_BASE ; 
 int UMIP_GDT_IDT_BASE_SIZE_32BIT ; 
 int UMIP_GDT_IDT_BASE_SIZE_64BIT ; 
 int UMIP_GDT_IDT_LIMIT_SIZE ; 
 int UMIP_INST_SGDT ; 
 int UMIP_INST_SIDT ; 
 int UMIP_INST_SMSW ; 
 int X86_MODRM_MOD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned long*,int) ; 

__attribute__((used)) static int emulate_umip_insn(struct insn *insn, int umip_inst,
			     unsigned char *data, int *data_size, bool x86_64)
{
	if (!data || !data_size || !insn)
		return -EINVAL;
	/*
	 * These two instructions return the base address and limit of the
	 * global and interrupt descriptor table, respectively. According to the
	 * Intel Software Development manual, the base address can be 24-bit,
	 * 32-bit or 64-bit. Limit is always 16-bit. If the operand size is
	 * 16-bit, the returned value of the base address is supposed to be a
	 * zero-extended 24-byte number. However, it seems that a 32-byte number
	 * is always returned irrespective of the operand size.
	 */
	if (umip_inst == UMIP_INST_SGDT || umip_inst == UMIP_INST_SIDT) {
		u64 dummy_base_addr;
		u16 dummy_limit = 0;

		/* SGDT and SIDT do not use registers operands. */
		if (X86_MODRM_MOD(insn->modrm.value) == 3)
			return -EINVAL;

		if (umip_inst == UMIP_INST_SGDT)
			dummy_base_addr = UMIP_DUMMY_GDT_BASE;
		else
			dummy_base_addr = UMIP_DUMMY_IDT_BASE;

		/*
		 * 64-bit processes use the entire dummy base address.
		 * 32-bit processes use the lower 32 bits of the base address.
		 * dummy_base_addr is always 64 bits, but we memcpy the correct
		 * number of bytes from it to the destination.
		 */
		if (x86_64)
			*data_size = UMIP_GDT_IDT_BASE_SIZE_64BIT;
		else
			*data_size = UMIP_GDT_IDT_BASE_SIZE_32BIT;

		memcpy(data + 2, &dummy_base_addr, *data_size);

		*data_size += UMIP_GDT_IDT_LIMIT_SIZE;
		memcpy(data, &dummy_limit, UMIP_GDT_IDT_LIMIT_SIZE);

	} else if (umip_inst == UMIP_INST_SMSW) {
		unsigned long dummy_value = CR0_STATE;

		/*
		 * Even though the CR0 register has 4 bytes, the number
		 * of bytes to be copied in the result buffer is determined
		 * by whether the operand is a register or a memory location.
		 * If operand is a register, return as many bytes as the operand
		 * size. If operand is memory, return only the two least
		 * siginificant bytes of CR0.
		 */
		if (X86_MODRM_MOD(insn->modrm.value) == 3)
			*data_size = insn->opnd_bytes;
		else
			*data_size = 2;

		memcpy(data, &dummy_value, *data_size);
	/* STR and SLDT  are not emulated */
	} else {
		return -EINVAL;
	}

	return 0;
}