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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ target_read_memory (int /*<<< orphan*/ ,unsigned char*,int) ; 

unsigned long
sparc_fetch_instruction (CORE_ADDR pc)
{
  unsigned char buf[4];
  unsigned long insn;
  int i;

  /* If we can't read the instruction at PC, return zero.  */
  if (target_read_memory (pc, buf, sizeof (buf)))
    return 0;

  insn = 0;
  for (i = 0; i < sizeof (buf); i++)
    insn = (insn << 8) | buf[i];
  return insn;
}