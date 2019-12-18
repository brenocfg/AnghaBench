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
typedef  int /*<<< orphan*/  break_insn ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */

__attribute__((used)) static const unsigned char *
sparc_breakpoint_from_pc (CORE_ADDR *pc, int *len)
{
  static unsigned char break_insn[] = { 0x91, 0xd0, 0x20, 0x01 };

  *len = sizeof (break_insn);
  return break_insn;
}