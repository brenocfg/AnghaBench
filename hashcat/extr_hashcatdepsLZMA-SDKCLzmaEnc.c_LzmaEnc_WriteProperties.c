#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int UInt32 ;
struct TYPE_2__ {int dictSize; int pb; int lp; scalar_t__ lc; } ;
typedef  scalar_t__ SizeT ;
typedef  int /*<<< orphan*/  SRes ;
typedef  scalar_t__ CLzmaEncHandle ;
typedef  TYPE_1__ CLzmaEnc ;
typedef  scalar_t__ Byte ;

/* Variables and functions */
 scalar_t__ LZMA_PROPS_SIZE ; 
 int /*<<< orphan*/  SZ_ERROR_PARAM ; 
 int /*<<< orphan*/  SZ_OK ; 

SRes LzmaEnc_WriteProperties(CLzmaEncHandle pp, Byte *props, SizeT *size)
{
  CLzmaEnc *p = (CLzmaEnc *)pp;
  unsigned i;
  UInt32 dictSize = p->dictSize;
  if (*size < LZMA_PROPS_SIZE)
    return SZ_ERROR_PARAM;
  *size = LZMA_PROPS_SIZE;
  props[0] = (Byte)((p->pb * 5 + p->lp) * 9 + p->lc);

  if (dictSize >= ((UInt32)1 << 22))
  {
    UInt32 kDictMask = ((UInt32)1 << 20) - 1;
    if (dictSize < (UInt32)0xFFFFFFFF - kDictMask)
      dictSize = (dictSize + kDictMask) & ~kDictMask;
  }
  else for (i = 11; i <= 30; i++)
  {
    if (dictSize <= ((UInt32)2 << i)) { dictSize = (2 << i); break; }
    if (dictSize <= ((UInt32)3 << i)) { dictSize = (3 << i); break; }
  }

  for (i = 0; i < 4; i++)
    props[1 + i] = (Byte)(dictSize >> (8 * i));
  return SZ_OK;
}