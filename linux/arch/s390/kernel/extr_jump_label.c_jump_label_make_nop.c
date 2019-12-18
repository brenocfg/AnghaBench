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
struct jump_entry {int dummy; } ;
struct insn {int opcode; int offset; } ;

/* Variables and functions */
 int jump_entry_code (struct jump_entry*) ; 
 int jump_entry_target (struct jump_entry*) ; 

__attribute__((used)) static void jump_label_make_nop(struct jump_entry *entry, struct insn *insn)
{
	/* brcl 0,offset */
	insn->opcode = 0xc004;
	insn->offset = (jump_entry_target(entry) - jump_entry_code(entry)) >> 1;
}