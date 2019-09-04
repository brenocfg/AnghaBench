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

unsigned Xz_ReadVarInt(const Byte *p, size_t maxSize, UInt64 *value)
{
  unsigned i, limit;
  *value = 0;
  limit = (maxSize > 9) ? 9 : (unsigned)maxSize;

  for (i = 0; i < limit;)
  {
    Byte b = p[i];
    *value |= (UInt64)(b & 0x7F) << (7 * i++);
    if ((b & 0x80) == 0)
      return (b == 0 && i != 1) ? 0 : i;
  }
  return 0;
}