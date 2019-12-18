#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int Range; int Code; TYPE_1__* Stream; scalar_t__ Bottom; scalar_t__ Low; } ;
struct TYPE_4__ {int (* Read ) (void*) ;} ;
typedef  TYPE_2__ CPpmd7z_RangeDec ;
typedef  int Bool ;

/* Variables and functions */
 int stub1 (void*) ; 

__attribute__((used)) static Bool Ppmd_RangeDec_Init(CPpmd7z_RangeDec *p)
{
  unsigned i;
  p->Low = p->Bottom = 0;
  p->Range = 0xFFFFFFFF;
  for (i = 0; i < 4; i++)
    p->Code = (p->Code << 8) | p->Stream->Read((void *)p->Stream);
  return (p->Code < 0xFFFFFFFF);
}