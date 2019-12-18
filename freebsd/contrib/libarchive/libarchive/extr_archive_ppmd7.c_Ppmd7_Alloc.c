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
typedef  scalar_t__ UInt32 ;
struct TYPE_4__ {scalar_t__ Base; scalar_t__ Size; scalar_t__ AlignOffset; } ;
typedef  TYPE_1__ CPpmd7 ;
typedef  int /*<<< orphan*/  Byte ;
typedef  int /*<<< orphan*/  Bool ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  Ppmd7_Free (TYPE_1__*) ; 
 int /*<<< orphan*/  True ; 
 scalar_t__ UNIT_SIZE ; 
 scalar_t__ malloc (scalar_t__) ; 

__attribute__((used)) static Bool Ppmd7_Alloc(CPpmd7 *p, UInt32 size)
{
  if (p->Base == 0 || p->Size != size)
  {
    /* RestartModel() below assumes that p->Size >= UNIT_SIZE
       (see the calculation of m->MinContext). */
    if (size < UNIT_SIZE) {
      return False;
    }
    Ppmd7_Free(p);
    p->AlignOffset =
      #ifdef PPMD_32BIT
        (4 - size) & 3;
      #else
        4 - (size & 3);
      #endif
    if ((p->Base = (Byte *)malloc(p->AlignOffset + size
        #ifndef PPMD_32BIT
        + UNIT_SIZE
        #endif
        )) == 0)
      return False;
    p->Size = size;
  }
  return True;
}