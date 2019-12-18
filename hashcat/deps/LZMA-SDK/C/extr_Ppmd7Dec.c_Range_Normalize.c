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
struct TYPE_3__ {int Range; int Code; int /*<<< orphan*/  Stream; } ;
typedef  TYPE_1__ CPpmd7z_RangeDec ;

/* Variables and functions */
 int IByteIn_Read (int /*<<< orphan*/ ) ; 
 int kTopValue ; 

__attribute__((used)) static void Range_Normalize(CPpmd7z_RangeDec *p)
{
  if (p->Range < kTopValue)
  {
    p->Code = (p->Code << 8) | IByteIn_Read(p->Stream);
    p->Range <<= 8;
    if (p->Range < kTopValue)
    {
      p->Code = (p->Code << 8) | IByteIn_Read(p->Stream);
      p->Range <<= 8;
    }
  }
}