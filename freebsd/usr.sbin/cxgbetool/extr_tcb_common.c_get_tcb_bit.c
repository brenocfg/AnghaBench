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

__attribute__((used)) static int
get_tcb_bit(unsigned char *A, int bit)
{
  int ret=0;
  int ix,shift;

  ix = 127 - (bit>>3);
  shift=bit&0x7;
  /*  prdbg("  ix: %u, shift=%u\n",ix,shift); */
  ret=(A[ix] >> shift) & 1;
  return ret;
}