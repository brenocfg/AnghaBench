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

/* Variables and functions */
 unsigned char hex (int /*<<< orphan*/ ) ; 
 scalar_t__ mem_err ; 
 int /*<<< orphan*/  set_mem_fault_trap (int) ; 

__attribute__((used)) static char *
hex2mem (unsigned char *buf, unsigned char *mem, int count, int may_fault)
{
  int i;
  unsigned char ch;

  set_mem_fault_trap(may_fault);

  for (i=0; i<count; i++)
    {
      ch = hex(*buf++) << 4;
      ch |= hex(*buf++);
      *mem++ = ch;
      if (mem_err)
	return 0;
    }

  set_mem_fault_trap(0);

  return mem;
}