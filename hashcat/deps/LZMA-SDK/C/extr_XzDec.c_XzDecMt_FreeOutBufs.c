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
struct TYPE_5__ {scalar_t__ unpackBlockMaxSize; int /*<<< orphan*/  allocMid; TYPE_1__* coders; } ;
struct TYPE_4__ {scalar_t__ outBufSize; int /*<<< orphan*/ * outBuf; } ;
typedef  TYPE_1__ CXzDecMtThread ;
typedef  TYPE_2__ CXzDecMt ;

/* Variables and functions */
 int /*<<< orphan*/  ISzAlloc_Free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int MTDEC__THREADS_MAX ; 

__attribute__((used)) static void XzDecMt_FreeOutBufs(CXzDecMt *p)
{
  unsigned i;
  for (i = 0; i < MTDEC__THREADS_MAX; i++)
  {
    CXzDecMtThread *coder = &p->coders[i];
    if (coder->outBuf)
    {
      ISzAlloc_Free(p->allocMid, coder->outBuf);
      coder->outBuf = NULL;
      coder->outBufSize = 0;
    }
  }
  p->unpackBlockMaxSize = 0;
}