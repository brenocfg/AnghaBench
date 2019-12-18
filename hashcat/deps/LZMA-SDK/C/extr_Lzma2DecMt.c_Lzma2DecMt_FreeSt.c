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
struct TYPE_4__ {int /*<<< orphan*/  vt; } ;
struct TYPE_5__ {scalar_t__ inBufSize; int /*<<< orphan*/ * inBuf; int /*<<< orphan*/  allocMid; scalar_t__ dec_created; TYPE_1__ alignOffsetAlloc; int /*<<< orphan*/  dec; } ;
typedef  TYPE_2__ CLzma2DecMt ;

/* Variables and functions */
 scalar_t__ False ; 
 int /*<<< orphan*/  ISzAlloc_Free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lzma2Dec_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Lzma2DecMt_FreeSt(CLzma2DecMt *p)
{
  if (p->dec_created)
  {
    Lzma2Dec_Free(&p->dec, &p->alignOffsetAlloc.vt);
    p->dec_created = False;
  }
  if (p->inBuf)
  {
    ISzAlloc_Free(p->allocMid, p->inBuf);
    p->inBuf = NULL;
  }
  p->inBufSize = 0;
}