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
struct TYPE_4__ {int /*<<< orphan*/ * p; int /*<<< orphan*/  (* Free ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/ * buf; TYPE_1__ StateCoder; } ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  TYPE_2__ CSeqInFilter ;

/* Variables and functions */
 int /*<<< orphan*/  ISzAlloc_Free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SeqInFilter_Free(CSeqInFilter *p, ISzAllocPtr alloc)
{
  if (p->StateCoder.p)
  {
    p->StateCoder.Free(p->StateCoder.p, alloc);
    p->StateCoder.p = NULL;
  }
  if (p->buf)
  {
    ISzAlloc_Free(alloc, p->buf);
    p->buf = NULL;
  }
}