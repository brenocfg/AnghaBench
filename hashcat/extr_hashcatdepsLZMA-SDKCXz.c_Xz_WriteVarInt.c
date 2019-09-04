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
typedef  int UInt64 ;
typedef  int Byte ;

/* Variables and functions */

unsigned Xz_WriteVarInt(Byte *buf, UInt64 v)
{
  unsigned i = 0;
  do
  {
    buf[i++] = (Byte)((v & 0x7F) | 0x80);
    v >>= 7;
  }
  while (v != 0);
  buf[(size_t)i - 1] &= 0x7F;
  return i;
}