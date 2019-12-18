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
typedef  size_t SizeT ;
typedef  int const Byte ;

/* Variables and functions */
 int GetUi32 (int const*) ; 
 int /*<<< orphan*/  SetUi32 (int const*,int) ; 

SizeT ARM_Convert(Byte *data, SizeT size, UInt32 ip, int encoding)
{
  Byte *p;
  const Byte *lim;
  size &= ~(size_t)3;
  ip += 4;
  p = data;
  lim = data + size;

  if (encoding)

  for (;;)
  {
    for (;;)
    {
      if (p >= lim)
        return p - data;
      p += 4;
      if (p[-1] == 0xEB)
        break;
    }
    {
      UInt32 v = GetUi32(p - 4);
      v <<= 2;
        v += ip + (UInt32)(p - data);
      v >>= 2;
      v &= 0x00FFFFFF;
      v |= 0xEB000000;
      SetUi32(p - 4, v);
    }
  }

  for (;;)
  {
    for (;;)
    {
      if (p >= lim)
        return p - data;
      p += 4;
      if (p[-1] == 0xEB)
        break;
    }
    {
      UInt32 v = GetUi32(p - 4);
      v <<= 2;
        v -= ip + (UInt32)(p - data);
      v >>= 2;
      v &= 0x00FFFFFF;
      v |= 0xEB000000;
      SetUi32(p - 4, v);
    }
  }
}