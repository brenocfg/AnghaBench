#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UInt32 ;
struct TYPE_4__ {int Size; int AlignOffset; int /*<<< orphan*/ * Base; } ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  TYPE_1__ CPpmd7 ;
typedef  int /*<<< orphan*/  Byte ;
typedef  int /*<<< orphan*/  BoolInt ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 scalar_t__ ISzAlloc_Alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Ppmd7_Free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  UNIT_SIZE ; 

BoolInt Ppmd7_Alloc(CPpmd7 *p, UInt32 size, ISzAllocPtr alloc)
{
  if (!p->Base || p->Size != size)
  {
    size_t size2;
    Ppmd7_Free(p, alloc);
    size2 = 0
      #ifndef PPMD_32BIT
      + UNIT_SIZE
      #endif
      ;
    p->AlignOffset =
      #ifdef PPMD_32BIT
        (4 - size) & 3;
      #else
        4 - (size & 3);
      #endif
    if ((p->Base = (Byte *)ISzAlloc_Alloc(alloc, p->AlignOffset + size + size2)) == 0)
      return False;
    p->Size = size;
  }
  return True;
}