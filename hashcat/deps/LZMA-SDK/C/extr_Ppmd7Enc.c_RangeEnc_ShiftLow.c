#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UInt32 ;
struct TYPE_3__ {int Low; int Cache; scalar_t__ CacheSize; int /*<<< orphan*/  Stream; } ;
typedef  TYPE_1__ CPpmd7z_RangeEnc ;
typedef  int Byte ;

/* Variables and functions */
 int /*<<< orphan*/  IByteOut_Write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void RangeEnc_ShiftLow(CPpmd7z_RangeEnc *p)
{
  if ((UInt32)p->Low < (UInt32)0xFF000000 || (unsigned)(p->Low >> 32) != 0)
  {
    Byte temp = p->Cache;
    do
    {
      IByteOut_Write(p->Stream, (Byte)(temp + (Byte)(p->Low >> 32)));
      temp = 0xFF;
    }
    while (--p->CacheSize != 0);
    p->Cache = (Byte)((UInt32)p->Low >> 24);
  }
  p->CacheSize++;
  p->Low = (UInt32)p->Low << 8;
}