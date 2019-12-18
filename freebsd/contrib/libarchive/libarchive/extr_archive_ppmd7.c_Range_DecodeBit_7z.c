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
typedef  int UInt32 ;
struct TYPE_3__ {int Range; int Code; } ;
typedef  TYPE_1__ CPpmd7z_RangeDec ;

/* Variables and functions */
 int /*<<< orphan*/  Range_Normalize (TYPE_1__*) ; 

__attribute__((used)) static UInt32 Range_DecodeBit_7z(void *pp, UInt32 size0)
{
  CPpmd7z_RangeDec *p = (CPpmd7z_RangeDec *)pp;
  UInt32 newBound = (p->Range >> 14) * size0;
  UInt32 symbol;
  if (p->Code < newBound)
  {
    symbol = 0;
    p->Range = newBound;
  }
  else
  {
    symbol = 1;
    p->Code -= newBound;
    p->Range -= newBound;
  }
  Range_Normalize(p);
  return symbol;
}