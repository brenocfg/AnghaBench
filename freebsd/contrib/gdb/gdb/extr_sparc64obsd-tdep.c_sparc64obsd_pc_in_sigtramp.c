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
typedef  int CORE_ADDR ;

/* Variables and functions */
 int sparc64obsd_page_size ; 
 unsigned long sparc_fetch_instruction (int) ; 

__attribute__((used)) static int
sparc64obsd_pc_in_sigtramp (CORE_ADDR pc, char *name)
{
  CORE_ADDR start_pc = (pc & ~(sparc64obsd_page_size - 1));
  unsigned long insn;

  if (name)
    return 0;

  /* Check for "restore %g0, SYS_sigreturn, %g1".  */
  insn = sparc_fetch_instruction (start_pc + 0xe8);
  if (insn != 0x83e82067)
    return 0;

  /* Check for "t ST_SYSCALL".  */
  insn = sparc_fetch_instruction (start_pc + 0xf0);
  if (insn != 0x91d02000)
    return 0;

  return 1;
}