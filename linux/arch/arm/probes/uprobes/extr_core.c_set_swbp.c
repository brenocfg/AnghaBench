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
struct mm_struct {int dummy; } ;
struct arch_uprobe {int /*<<< orphan*/  bpinsn; } ;

/* Variables and functions */
 int /*<<< orphan*/  __opcode_to_mem_arm (int /*<<< orphan*/ ) ; 
 int uprobe_write_opcode (struct arch_uprobe*,struct mm_struct*,unsigned long,int /*<<< orphan*/ ) ; 

int set_swbp(struct arch_uprobe *auprobe, struct mm_struct *mm,
	     unsigned long vaddr)
{
	return uprobe_write_opcode(auprobe, mm, vaddr,
		   __opcode_to_mem_arm(auprobe->bpinsn));
}