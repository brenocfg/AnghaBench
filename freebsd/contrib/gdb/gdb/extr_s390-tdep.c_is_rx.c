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
typedef  int bfd_byte ;

/* Variables and functions */

__attribute__((used)) static int
is_rx (bfd_byte *insn, int op,
       unsigned int *r1, unsigned int *d2, unsigned int *x2, unsigned int *b2)
{
  if (insn[0] == op)
    {
      *r1 = (insn[1] >> 4) & 0xf;
      *x2 = insn[1] & 0xf;
      *b2 = (insn[2] >> 4) & 0xf;
      *d2 = ((insn[2] & 0xf) << 8) | insn[3];
      return 1;
    }
  else
    return 0;
}