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
struct TYPE_3__ {scalar_t__ inBufSize; int /*<<< orphan*/ * inBuf; int /*<<< orphan*/  allocMid; scalar_t__ outBufSize; int /*<<< orphan*/ * outBuf; int /*<<< orphan*/  dec; } ;
typedef  TYPE_1__ CXzDecMt ;

/* Variables and functions */
 int /*<<< orphan*/  ISzAlloc_Free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XzUnpacker_Free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void XzDecMt_FreeSt(CXzDecMt *p)
{
  XzUnpacker_Free(&p->dec);
  
  if (p->outBuf)
  {
    ISzAlloc_Free(p->allocMid, p->outBuf);
    p->outBuf = NULL;
  }
  p->outBufSize = 0;
  
  if (p->inBuf)
  {
    ISzAlloc_Free(p->allocMid, p->inBuf);
    p->inBuf = NULL;
  }
  p->inBufSize = 0;
}