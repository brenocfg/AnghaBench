#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int opcode; } ;

/* Variables and functions */
 int SPU_DISASM_TBL_SIZE ; 
 TYPE_1__** spu_disassemble_table ; 
 int spu_num_opcodes ; 
 TYPE_1__* spu_opcodes ; 

__attribute__((used)) static void
init_spu_disassemble (void)
{
  int i;

  /* If two instructions have the same opcode then we prefer the first
   * one.  In most cases it is just an alternate mnemonic. */
  for (i = 0; i < spu_num_opcodes; i++)
    {
      int o = spu_opcodes[i].opcode;
      if (o >= SPU_DISASM_TBL_SIZE)
	continue; /* abort (); */
      if (spu_disassemble_table[o] == 0)
	spu_disassemble_table[o] = &spu_opcodes[i];
    }
}