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
struct TYPE_2__ {scalar_t__* bytes; } ;
struct insn {scalar_t__ length; void* next_byte; void* kaddr; TYPE_1__ opcode; } ;
typedef  int /*<<< orphan*/  kprobe_opcode_t ;

/* Variables and functions */
 scalar_t__ BREAKPOINT_INSTRUCTION ; 
 scalar_t__ INT3_SIZE ; 
 int MAX_INSN_SIZE ; 
 unsigned long RELATIVEJUMP_SIZE ; 
 int /*<<< orphan*/  RELATIVE_ADDR_SIZE ; 
 scalar_t__ __entry_text_end ; 
 scalar_t__ __entry_text_start ; 
 scalar_t__ __irqentry_text_end ; 
 scalar_t__ __irqentry_text_start ; 
 int /*<<< orphan*/  insn_get_length (struct insn*) ; 
 scalar_t__ insn_is_indirect_jump (struct insn*) ; 
 scalar_t__ insn_jump_into_range (struct insn*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kallsyms_lookup_size_offset (unsigned long,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  kernel_insn_init (struct insn*,void*,int) ; 
 unsigned long recover_probed_instruction (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ search_exception_tables (unsigned long) ; 

__attribute__((used)) static int can_optimize(unsigned long paddr)
{
	unsigned long addr, size = 0, offset = 0;
	struct insn insn;
	kprobe_opcode_t buf[MAX_INSN_SIZE];

	/* Lookup symbol including addr */
	if (!kallsyms_lookup_size_offset(paddr, &size, &offset))
		return 0;

	/*
	 * Do not optimize in the entry code due to the unstable
	 * stack handling and registers setup.
	 */
	if (((paddr >= (unsigned long)__entry_text_start) &&
	     (paddr <  (unsigned long)__entry_text_end)) ||
	    ((paddr >= (unsigned long)__irqentry_text_start) &&
	     (paddr <  (unsigned long)__irqentry_text_end)))
		return 0;

	/* Check there is enough space for a relative jump. */
	if (size - offset < RELATIVEJUMP_SIZE)
		return 0;

	/* Decode instructions */
	addr = paddr - offset;
	while (addr < paddr - offset + size) { /* Decode until function end */
		unsigned long recovered_insn;
		if (search_exception_tables(addr))
			/*
			 * Since some fixup code will jumps into this function,
			 * we can't optimize kprobe in this function.
			 */
			return 0;
		recovered_insn = recover_probed_instruction(buf, addr);
		if (!recovered_insn)
			return 0;
		kernel_insn_init(&insn, (void *)recovered_insn, MAX_INSN_SIZE);
		insn_get_length(&insn);
		/* Another subsystem puts a breakpoint */
		if (insn.opcode.bytes[0] == BREAKPOINT_INSTRUCTION)
			return 0;
		/* Recover address */
		insn.kaddr = (void *)addr;
		insn.next_byte = (void *)(addr + insn.length);
		/* Check any instructions don't jump into target */
		if (insn_is_indirect_jump(&insn) ||
		    insn_jump_into_range(&insn, paddr + INT3_SIZE,
					 RELATIVE_ADDR_SIZE))
			return 0;
		addr += insn.length;
	}

	return 1;
}