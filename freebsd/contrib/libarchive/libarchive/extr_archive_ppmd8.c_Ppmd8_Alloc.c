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
struct TYPE_4__ {scalar_t__ Base; int Size; int AlignOffset; } ;
typedef  TYPE_1__ CPpmd8 ;
typedef  int /*<<< orphan*/  Byte ;
typedef  int /*<<< orphan*/  Bool ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  Ppmd8_Free (TYPE_1__*) ; 
 int /*<<< orphan*/  True ; 
 scalar_t__ malloc (int) ; 

Bool Ppmd8_Alloc(CPpmd8 *p, UInt32 size)
{
  if (p->Base == 0 || p->Size != size)
  {
    Ppmd8_Free(p);
    p->AlignOffset =
      #ifdef PPMD_32BIT
        (4 - size) & 3;
      #else
        4 - (size & 3);
      #endif
    if ((p->Base = (Byte *)malloc(p->AlignOffset + size)) == 0)
      return False;
    p->Size = size;
  }
  return True;
}