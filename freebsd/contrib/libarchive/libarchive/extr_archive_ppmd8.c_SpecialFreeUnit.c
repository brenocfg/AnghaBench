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
typedef  int /*<<< orphan*/  UInt32 ;
struct TYPE_4__ {int /*<<< orphan*/ * UnitsStart; } ;
typedef  TYPE_1__ CPpmd8 ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY_NODE ; 
 int /*<<< orphan*/  InsertNode (TYPE_1__*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIT_SIZE ; 

__attribute__((used)) static void SpecialFreeUnit(CPpmd8 *p, void *ptr)
{
  if ((Byte *)ptr != p->UnitsStart)
    InsertNode(p, ptr, 0);
  else
  {
    #ifdef PPMD8_FREEZE_SUPPORT
    *(UInt32 *)ptr = EMPTY_NODE; /* it's used for (Flags == 0xFF) check in RemoveBinContexts */
    #endif
    p->UnitsStart += UNIT_SIZE;
  }
}