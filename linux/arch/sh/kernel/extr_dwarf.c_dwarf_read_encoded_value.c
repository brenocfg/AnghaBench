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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
#define  DW_EH_PE_absptr 131 
#define  DW_EH_PE_pcrel 130 
#define  DW_EH_PE_sdata4 129 
#define  DW_EH_PE_udata4 128 
 int /*<<< orphan*/  UNWINDER_BUG () ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,unsigned long*) ; 
 unsigned long get_unaligned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,char) ; 

__attribute__((used)) static int dwarf_read_encoded_value(char *addr, unsigned long *val,
				    char encoding)
{
	unsigned long decoded_addr = 0;
	int count = 0;

	switch (encoding & 0x70) {
	case DW_EH_PE_absptr:
		break;
	case DW_EH_PE_pcrel:
		decoded_addr = (unsigned long)addr;
		break;
	default:
		pr_debug("encoding=0x%x\n", (encoding & 0x70));
		UNWINDER_BUG();
	}

	if ((encoding & 0x07) == 0x00)
		encoding |= DW_EH_PE_udata4;

	switch (encoding & 0x0f) {
	case DW_EH_PE_sdata4:
	case DW_EH_PE_udata4:
		count += 4;
		decoded_addr += get_unaligned((u32 *)addr);
		__raw_writel(decoded_addr, val);
		break;
	default:
		pr_debug("encoding=0x%x\n", encoding);
		UNWINDER_BUG();
	}

	return count;
}