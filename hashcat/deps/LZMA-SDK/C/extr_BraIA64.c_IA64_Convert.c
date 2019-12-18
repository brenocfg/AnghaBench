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
typedef  int UInt32 ;
typedef  int SizeT ;
typedef  int Byte ;

/* Variables and functions */
 unsigned int GetUi32 (int*) ; 
 int /*<<< orphan*/  SetUi32 (int*,unsigned int) ; 

SizeT IA64_Convert(Byte *data, SizeT size, UInt32 ip, int encoding)
{
  SizeT i;
  if (size < 16)
    return 0;
  size -= 16;
  i = 0;
  do
  {
    unsigned m = ((UInt32)0x334B0000 >> (data[i] & 0x1E)) & 3;
    if (m)
    {
      m++;
      do
      {
        Byte *p = data + (i + (size_t)m * 5 - 8);
        if (((p[3] >> m) & 15) == 5
            && (((p[-1] | ((UInt32)p[0] << 8)) >> m) & 0x70) == 0)
        {
          unsigned raw = GetUi32(p);
          unsigned v = raw >> m;
          v = (v & 0xFFFFF) | ((v & (1 << 23)) >> 3);
          
          v <<= 4;
          if (encoding)
            v += ip + (UInt32)i;
          else
            v -= ip + (UInt32)i;
          v >>= 4;
          
          v &= 0x1FFFFF;
          v += 0x700000;
          v &= 0x8FFFFF;
          raw &= ~((UInt32)0x8FFFFF << m);
          raw |= (v << m);
          SetUi32(p, raw);
        }
      }
      while (++m <= 4);
    }
    i += 16;
  }
  while (i <= size);
  return i;
}