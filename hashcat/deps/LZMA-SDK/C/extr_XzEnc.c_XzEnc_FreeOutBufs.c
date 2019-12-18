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
struct TYPE_3__ {scalar_t__ outBufSize; int /*<<< orphan*/ ** outBufs; int /*<<< orphan*/  alloc; } ;
typedef  TYPE_1__ CXzEnc ;

/* Variables and functions */
 int /*<<< orphan*/  ISzAlloc_Free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int MTCODER__BLOCKS_MAX ; 

__attribute__((used)) static void XzEnc_FreeOutBufs(CXzEnc *p)
{
  unsigned i;
  for (i = 0; i < MTCODER__BLOCKS_MAX; i++)
    if (p->outBufs[i])
    {
      ISzAlloc_Free(p->alloc, p->outBufs[i]);
      p->outBufs[i] = NULL;
    }
  p->outBufSize = 0;
}