#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int UInt32 ;
struct TYPE_7__ {int (* Read ) (TYPE_3__*) ;} ;
struct TYPE_5__ {TYPE_3__* In; } ;
struct TYPE_6__ {int Range; int Low; int Code; TYPE_1__ Stream; } ;
typedef  TYPE_2__ CPpmd8 ;

/* Variables and functions */
 int kBot ; 
 int kTop ; 
 int stub1 (TYPE_3__*) ; 

__attribute__((used)) static void RangeDec_Decode(CPpmd8 *p, UInt32 start, UInt32 size)
{
  start *= p->Range;
  p->Low += start;
  p->Code -= start;
  p->Range *= size;

  while ((p->Low ^ (p->Low + p->Range)) < kTop ||
      (p->Range < kBot && ((p->Range = (0 - p->Low) & (kBot - 1)), 1)))
  {
    p->Code = (p->Code << 8) | p->Stream.In->Read(p->Stream.In);
    p->Range <<= 8;
    p->Low <<= 8;
  }
}