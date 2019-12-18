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
is_ri (bfd_byte *insn, int op1, int op2, unsigned int *r1, int *i2)
{
  if (insn[0] == op1 && (insn[1] & 0xf) == op2)
    {
      *r1 = (insn[1] >> 4) & 0xf;
      /* i2 is a 16-bit signed quantity.  */
      *i2 = (((insn[2] << 8) | insn[3]) ^ 0x8000) - 0x8000;
      return 1;
    }
  else
    return 0;
}